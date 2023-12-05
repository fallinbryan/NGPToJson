#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "dependencies/json/json.hpp"
#include "dependencies/zlib/zlib.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input filename>  <output filename>" << std::endl;
        return 1;
    }

    std::vector<uint8_t> buffer(1024 * 1024);
    std::vector<uint8_t> decompressed_data;

    std::string filename = argv[1];
    std::string outfile = argv[2];

    try
    {
        std::cout << "Opening " << filename << std::endl;
        std::ifstream file(filename, std::ios_base::in | std::ios_base::binary);
        if (!file.is_open())
        {
            std::cerr << "Cannot open file." << std::endl;
            return 1;
        }

        z_stream strm;
        memset(&strm, 0, sizeof(strm));
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;

        int ret = inflateInit2(&strm, 16 + MAX_WBITS);
        if (ret != Z_OK)
        {
            std::cerr << "inflateInit2 failed." << std::endl;
            return 1;
        }

        std::cout << "Reading " << filename << std::endl;
        while (!file.eof())
        {
            file.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
            strm.avail_in = file.gcount();
            if (strm.avail_in == 0)
            {
                break;
            }

            strm.next_in = buffer.data();

            do
            {
                std::vector<uint8_t> out(buffer.size());
                strm.avail_out = out.size();
                strm.next_out = out.data();

                ret = inflate(&strm, Z_NO_FLUSH);
                assert(ret != Z_STREAM_ERROR);

                switch (ret)
                {
                case Z_NEED_DICT:
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&strm);
                    std::cerr << "Decompression error." << std::endl;
                    return 1;
                }

                size_t have = out.size() - strm.avail_out;
                decompressed_data.insert(decompressed_data.end(), out.data(), out.data() + have);
            } while (strm.avail_out == 0);
        }

        // Clean up
        file.close();
        (void)inflateEnd(&strm);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    try
    {
        // Open the MessagePack file
        // std::ifstream messagepack_file(filename, std::ios::binary);

        // if (!messagepack_file.is_open())
        //{
        //     throw std::runtime_error("Cannot open MessagePack file.");
        // }

        // Read the MessagePack data into a vector

        // std::vector<uint8_t> messagepack_data(
        //     (std::istreambuf_iterator<char>(messagepack_file)),
        //     std::istreambuf_iterator<char>());
        // messagepack_file.close();

        std::cout << "data loaded into vector size: " << decompressed_data.size() << std::endl;

        // Deserialize MessagePack to JSON
        std::cout << "Deserializing " << filename << " to json" << std::endl;
        nlohmann::json json_obj = nlohmann::json::from_msgpack(decompressed_data);

        // Output the JSON object to console (optional)
        // std::cout << "Deserialized JSON: " << json_obj.dump(4) << std::endl;

        // Write the JSON object to a file
        std::ofstream json_file(outfile);
        json_file << json_obj.dump(-1); // 4 is for pretty printing
        json_file.close();

        std::cout << "JSON data written to " << outfile << " file" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

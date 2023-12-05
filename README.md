# Nvidia Instant-NGP Snapshot to JSON Converter

This utility provides a simple and efficient way to convert Nvidia Instant-NGP snapshot files into JSON format. It's designed to help researchers and developers easily port their trained Neural Radiance Fields (NeRF) models into various applications by overcoming the inconvenience of dealing with gzipped MessagePack serialized data.

## Description

Nvidia Instant-NGP provides an option to save snapshots of trained NeRF models, which are stored in a gzipped MessagePack serialized format. This format, while efficient for storage, is not immediately usable in other applications that require a JSON format. This utility simplifies the process by converting these snapshot files into a more accessible JSON format.

## Features

- **Easy Conversion**: Convert Nvidia Instant-NGP snapshot files to JSON with a simple command.
- **Efficient Processing**: Handles gzipped MessagePack serialized data seamlessly.
- **Wide Applicability**: Useful for researchers and developers looking to integrate NeRF models into various platforms.

## Getting Started

### Prerequisites

Ensure you have a C++ compiler and make utility installed on your system. This project also includes `zlib` for decompression and `nlohmann/json` for JSON handling.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/fallinbryan/NGPToJson.git
   ```
2. Navigate to the project directory:
   ```bash
   cd NGPToJson
   ```
3. Compile the utility:
   ```bash
   make ngp2json
   ```

### Usage

Run the utility with the path to your Nvidia Instant-NGP snapshot file:

```bash
./ngp2json path/to/snapshot/file path/to/snapshot.json
```

The utility will output a JSON file containing the trained NeRF model.

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Contact

Bryan Fallin - fallinbryan@gmail.com

Project Link: [https://github.com/fallinbryan/NGPToJson](https://github.com/fallinbryan/NGPToJson)

## Acknowledgments

- [Nvidia Instant-NGP](https://github.com/NVlabs/instant-ngp)
- [nlohmann/json](https://github.com/nlohmann/json) for JSON handling
- [zlib](https://zlib.net/) for decompression support
- ChatGPT-4 by OpenAI for assistance with C++ code


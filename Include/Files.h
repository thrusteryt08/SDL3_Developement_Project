#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include"Console.h"

using namespace std;

namespace AxionForge {

	class File {
	private:
		const string path;

	public:
		explicit File(const string& path)
			: path(path) {
		}

		// ---------- INFO ----------

		/*const string& Path() const {
			return path;
		}

		bool Exists() const {
			return filesystem::exists(path);
		}

		bool IsDirectory() const {
			return filesystem::is_directory(path);
		}

		uint64_t Size() const {
			if (!Exists())
				return 0;
			return filesystem::file_size(path);
		}*/

		// ---------- READ ----------

		bool ReadText(string& outText) const {
			ifstream file(path, ios::in | ios::binary);
			if (!file.is_open()) {
				Console::Error("Failed to read file: " + path);
				return false;
			}

			file.seekg(0, ios::end);
			outText.resize(static_cast<size_t>(file.tellg()));
			file.seekg(0, ios::beg);

			file.read(&outText[0], outText.size());
			return true;
		}

		bool ReadLines(vector<string>& outLines) const {
			ifstream file(path, ios::in);
			if (!file.is_open()) {
				Console::Error("Failed to read lines: " + path);
				return false;
			}

			string line;
			while (getline(file, line)) {
				outLines.push_back(line);
			}
			return true;
		}

		bool ReadBinary(vector<uint8_t>& outData) const {
			ifstream file(path, ios::in | ios::binary);
			if (!file.is_open()) {
				Console::Error("Failed to read binary file: " + path);
				return false;
			}

			file.seekg(0, ios::end);
			outData.resize(static_cast<size_t>(file.tellg()));
			file.seekg(0, ios::beg);

			file.read(reinterpret_cast<char*>(outData.data()), outData.size());
			return true;
		}

		// ---------- WRITE ----------

		bool OverWriteText(const string& text) const {
			ofstream file(path, ios::out | ios::binary | ios::trunc);
			if (!file.is_open()) {
				Console::Error("Failed to overwrite file: " + path);
				return false;
			}

			file.write(text.data(), text.size());
			return file.good();
		}

		bool AppendText(const string& text) const {
			ofstream file(path, ios::out | ios::binary | ios::app);
			if (!file.is_open()) {
				Console::Error("Failed to append file: " + path);
				return false;
			}

			file.write(text.data(), text.size());
			return file.good();
		}

		bool WriteBinary(const void* data, size_t size) const {
			ofstream file(path, ios::out | ios::binary | ios::trunc);
			if (!file.is_open()) {
				Console::Error("Failed to write binary file: " + path);
				return false;
			}

			file.write(reinterpret_cast<const char*>(data), size);
			return file.good();
		}

		// ---------- FILE OPS ----------

		bool Clear() const {
			ofstream file(path, ios::out | ios::trunc);
			return file.is_open();
		}

		/*bool Delete() const {
			if (!Exists())
				return false;
			return filesystem::remove(path);
		}

		bool CopyTo(const string& destination) const {
			if (!Exists())
				return false;

			filesystem::copy_file(
				path,
				destination,
				filesystem::copy_options::overwrite_existing
			);
			return true;
		}

		bool MoveTo(const string& destination) const {
			if (!Exists())
				return false;

			filesystem::rename(path, destination);
			return true;
		}*/
	};

}
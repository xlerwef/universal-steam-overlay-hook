#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "stdio.h"

class ModuleSignature {
public:
	ModuleSignature(const std::string& moduleName, const std::string& patternString) {
		m_moduleName = moduleName;
		m_patternString = patternString;
	}

	void* find() {
		HMODULE hModule = GetModuleHandleA(m_moduleName.c_str());
		if (hModule == nullptr) {
			std::cerr << "Error: Module not found: " << m_moduleName << std::endl;
			return nullptr;
		}

		std::istringstream iss(m_patternString);
		std::string byteString;
		std::vector<byte> pattern;
		std::vector<byte> mask;
		while (std::getline(iss, byteString, ' ')) {
			if (byteString == "?") {
				pattern.push_back(0); // Wildcard byte
				mask.push_back(0);
			}
			else {
				unsigned int byteValue;
				std::stringstream ss;
				ss << std::hex << byteString;
				ss >> byteValue;
				pattern.push_back((byte)byteValue);
				mask.push_back(0xFF);
			}
		}

		size_t moduleSize = 0;
		void* currentAddress = (void*)hModule;
		while (true) {
			MEMORY_BASIC_INFORMATION mbi;
			if (VirtualQuery(currentAddress, &mbi, sizeof(mbi)) > 0) {
				moduleSize += mbi.RegionSize;
				currentAddress = (void*)((byte*)currentAddress + mbi.RegionSize);
				if ((byte*)currentAddress > (byte*)hModule + 0x1000000) {
					std::cerr << "Error: Exceeded assumed module size!" << std::endl;
					break;
				}
			}
			else {
				break;
			}
		}

		byte* address = reinterpret_cast<byte*>(hModule);
		for (size_t i = 0; i < moduleSize - pattern.size(); ++i) {
			bool match = true;
			for (size_t j = 0; j < pattern.size(); ++j) {
				if (mask[j] == 0xFF && address[i + j] != pattern[j]) {
					match = false;
					break;
				}
			}
			if (match) {
				return address + i;
			}
		}

		return nullptr;

	}
private:
	std::string m_moduleName;
	std::string m_patternString;
};

//0305F708
const std::string entity_list_pattern = std::string("8B 83 D8 00 00 00 41 89 46 08 F3 41 0F 11 76 24");
const std::string entity_list_start_pattern = std::string("40 53 41 54 41 57 48 81 EC B0 00 00 00 4C 8B E1 4C 8B FA 48 8D 8C 24 E0 00 00 00 E8 C0 7A 4A FF 48 8B 9C 24 E0 00 00 00 48 85 DB 0F 84 63 03 00 00");
const std::string steam_create_hook_pattern = std::string("48 89 5C 24 ? 57 48 83 EC ? 33 C0");
// Old Sig: 48 89 6C 24 ? 48 89 74 24 ? 41 56 48 83 EC ? 41 8B E8
const std::string steam_present_hook_pattern = std::string("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 20 41");
const std::string entity_move_hook_pattern = std::string("48 89 5C 24 18 57 48 83 EC 20 8B 41 10 33 FF");
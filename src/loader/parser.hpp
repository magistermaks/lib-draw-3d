#pragma once

#include <include/external.hpp>
#include <util/helper.hpp>
#include <util/buffer.hpp>

class Parser {

	private: 

		std::ifstream file;

	public:

		Parser(const std::string& path) : file(path) {
			if( !this->file.is_open() ) {
				logger::warn("Failed to open file: '", path, "'!");
			}
		}

		void load() {
			std::vector<std::string> vec;
			std::string line;

			int counter = 1;

			while( getline(this->file, line) ) {
				split(vec, line, ' ');

				if(vec[0] != "#" && vec.size() > 0) {
					this->handle(vec, counter);
				}

				counter ++;
				vec.clear();
			}
		}

	protected:

		virtual void handle( std::vector<std::string>& parts, int line ) {
			// do nothing by default
		}

};

class ObjParser : public Parser {

	private:

		FastBuffer<glm::vec3> v;
		FastBuffer<glm::vec3> n;
		FastBuffer<glm::vec2> t;
		std::string name = "default";

		std::unordered_map<std::string, FastBuffer<float>> things;
		FastBuffer<float>* current = nullptr;

		float vertex[8];
		int offset[3];

		static glm::vec3 cast3f( std::vector<std::string>& parts, const int offset ) {
			return glm::vec3( std::stof(parts[offset + 0]), std::stof(parts[offset + 1]), std::stof(parts[offset + 2]) );
		}

		static glm::vec2 cast2f( std::vector<std::string>& parts, const int offset ) {
			return glm::vec2( std::stof(parts[offset + 0]), std::stof(parts[offset + 1]) );
		}

		void face( int type, int index ) {
			switch(type) {
				case 0: memcpy( this->vertex + offset[type], v.data(index - 1), 3 * sizeof(float) ); break; // v
				case 1: memcpy( this->vertex + offset[type], t.data(index - 1), 2 * sizeof(float) ); break; // t
				case 2: memcpy( this->vertex + offset[type], n.data(index - 1), 3 * sizeof(float) ); break; // n
			}
		}

	public:

		ObjParser(const std::string& path) : Parser(path) {
			this->current = &(things[this->name]);
			this->format(0, 3, 5);
		}

		FastBuffer<float>& get(const std::string& name) {
			return this->things.at(name);
		}

		FastBuffer<float>& get() {
			return *current;
		}

		void format(int v, int t, int n) {
			offset[0] = v;
			offset[1] = t;
			offset[2] = n;
		}

	protected:

		void handle( std::vector<std::string>& parts, int line ) {
			const std::string& c = parts[0];
			const int args = parts.size() - 1;

			if( c == "o" && args == 1 ) {
				name = parts[1];
				this->current = &(things[name]);
			}else

			if( c == "v" && args == 3 ) {
				v.insert( cast3f(parts, 1) );
			}else

			if( c == "vn" && args == 3 ) {
				n.insert( cast3f(parts, 1) );
			}else

			if( c == "vt" && args == 2 ) {
				t.insert( cast2f(parts, 1) );
			}else

			if( c == "f" && args == 3 ) {
				std::vector<std::string> vec;

				for( int i = 1; i <= 3; i ++ ) {
					split(vec, parts[i], '/');

					for( int j = 0; j < 3 && j < vec.size(); j ++ ) {
						face(j, std::stoi(vec[j]));
					}

					current->insert(this->vertex, 8);
					vec.clear();
				}

				
				
			}else

			logger::warn("Invalid or unsuported OBJ command at line: ", line);
		}

};


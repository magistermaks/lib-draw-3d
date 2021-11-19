#pragma once

#include <include/external.hpp>
#include <renderer/texture.hpp>

#include "library.hpp"
#include "parser_mtl.hpp"
#include "parser_obj.hpp"

class Resource {

	private:

		static std::unordered_map<std::string, Texture*> textures;
		static std::unordered_map<std::string, MtlParser> mtls;
		static std::unordered_map<std::string, ObjParser> objs;
	
	public:

		static Texture* texture(const std::string& path);
		static MtlParser& material(const std::string& path);
		static ObjParser& object(const std::string& path);

		static void clean();

};


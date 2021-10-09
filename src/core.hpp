#pragma once

#include <include/config.hpp>
#include <include/external.hpp>
#include <include/forward.hpp>

// internal
#include "logger.hpp"
#include "glhelper.hpp"
#include "camera.hpp"
#include "util/buffer.hpp"
#include "util/trait.hpp"
#include "util/charset.hpp"
#include "util/thread_pool.hpp"
#include "renderer/shader.hpp"
#include "renderer/renderer.hpp"
#include "renderer/texture.hpp"
#include "renderer/vertex.hpp"
#include "renderer/matrix.hpp"
#include "renderer/context.hpp"
#include "renderer/light.hpp"
#include "renderer/uniform.hpp"
#include "renderer/storage.hpp"

// When adding a file here, remember to add its forward definition to the 'include/forward.hpp'!
// Include this file to gain access to all LT3D components, external libraries and macros.
// If your component is to be used in a header file, it MUST NOT include core.hpp, and can only use headers from the 'include/' directory


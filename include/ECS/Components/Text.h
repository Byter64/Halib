#pragma once
#define GLT_IMPLEMENTATION
#define GLT_MANUAL_VIEWPORT
#include "glad/glad.h"
#include "../glText/gltext.h"
#include "glm/glm.hpp"
#include <memory>
#include <string>

namespace Engine
{
    class TextRenderSystem;
    struct Text
    {
        friend class TextRenderSystem;

        enum Alignment {
            Left = GLT_LEFT,
            Top = GLT_TOP,
            Center = GLT_CENTER,
            Bottom = GLT_BOTTOM,
            Right = GLT_RIGHT
        };

        float scale;
        glm::vec2 position{};
        Alignment horizontalAlignment = Left;
        Alignment verticalAlignment = Top;
    private:
        std::unique_ptr<GLTtext> text;
        std::string string;
    public:
        Text();
        explicit Text(std::string string);
        Text (Text& other);

        Text& operator=(Text& other);
        Text& operator=(Text&& other) = default;

        void SetText(std::string string);
        std::string& GetText();
    };

} // Engine

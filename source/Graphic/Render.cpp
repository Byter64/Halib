#include "Graphic/Render.h"

void Halib::WaitForGPU()
{
	while(Hall::GetIsGPUBusy());
}

void Halib::Draw(Image &image, VecI2 position)
{
	WaitForGPU();

#ifdef DESKTOP
	if(image.GetWasDataRequested())
	{
		Hall::UpdateRaylibTexture((Hall::Color*)image.GetData());
	}
#endif

	Hall::SetImage((Hall::Color*)image.GetData(), image.GetWidth());
	Hall::SetExcerpt(0, 0, image.GetWidth(), image.GetHeight());
	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::MEMORY);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetScreenPosition(position.x, position.y);

	Hall::Draw();
}

void Halib::Draw(const std::string &text, VecI2 position, Font& font, Color color)
{
	Hall::SetColorTable(Hall::BIT_1);
	Hall::SetColorSource(Hall::MEMORY);
	FT_Face face = font.GetFace();
	for(char c : text)
	{
		unsigned int glyph_index = FT_Get_Char_Index(face, c);
		FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
		
		WaitForGPU();
		Hall::SetImage((Hall::IndexContainer*)face->glyph->bitmap.buffer, face->glyph->bitmap.width);
		Hall::SetScreenPosition(position.x, position.y);
		Hall::Draw();
		
		position.x += face->glyph->advance.x / 64; //??
	}
}

void Halib::Draw(const Rectangle &rect, VecI2 position, Color color)
{
	WaitForGPU();

	//This is ugly but I want to hide color.color. I hope the compiler optimises this away
	Hall::Color* hallColor = (Hall::Color*)(&color);

	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColor(*hallColor);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::COLOR);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetRectangle(rect.x, rect.y, rect.width, rect.height);

	Hall::Draw();
}


void Halib::Show()
{
	WaitForGPU();

	bool isVsync = Hall::GetVSync();
	bool newIsVsync = Hall::GetVSync();
	while(!(!isVsync && newIsVsync))
	{
		isVsync = newIsVsync;
		newIsVsync = Hall::GetVSync();
	}
	
	Hall::SetCommandSwapBuffers();
}

void Halib::Clear(Halib::Color color)
{
	WaitForGPU();

	//This is ugly but I want to hide color.color. I hope the compiler optimises this away
	Hall::Color* hallColor = (Hall::Color*)(&color);

	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColor(*hallColor);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::COLOR);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetRectangle(0, 0, Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT);

	Hall::Draw();
}

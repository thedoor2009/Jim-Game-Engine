#ifndef RENDER_H
#define RENDERE_H

#include "Spirte.h"
#include "SharedPtr.h"
#include <vector>

namespace JimEngine
{
	class Render
	{
	public:
		Render(void)
		{
		}

		void Destory(void)
		{
			for(unsigned int i = 0; i < m_renderSpriteArray.size(); i++)
			{
				m_renderSpriteArray.erase(m_renderSpriteArray.begin() + i);
			}
		}

		void Add(JimEngine::Ptr::SharePtr<JimEngine::Sprite> i_sprite);
		void Draw(void);
		void isMarkDeath(void);

	private:
		std::vector<JimEngine::Ptr::SharePtr<JimEngine::Sprite>> m_renderSpriteArray;
	};
}
#endif
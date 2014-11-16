#include "Render.h"

namespace JimEngine
{
	void Render::Add(JimEngine::Ptr::SharePtr<JimEngine::Sprite> i_sprite)
	{
		m_renderSpriteArray.push_back(i_sprite);
	}

	void Render::Draw(void)
	{
		isMarkDeath();
		for(unsigned int i = 0; i < m_renderSpriteArray.size();i++)
		{
			m_renderSpriteArray.at(i)->Draw();
		}
	}

	void Render::isMarkDeath(void)
	{
		for(unsigned int i = 0; i < m_renderSpriteArray.size(); i++)
		{
			if(m_renderSpriteArray.at(i)->Get_Death())
			{
				m_renderSpriteArray.erase(m_renderSpriteArray.begin() + i);
			}
		}
	}
}
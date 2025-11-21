#include "Texture2D.h"

namespace Renderer {
	Texture2D::Texture2D(const GLuint width,const GLuint height,const unsigned char *data,
		const unsigned int channels,const GLenum filter, const GLenum wrapMode) : m_height(height),m_width(width)
	{
		switch (channels) {
			case 4:
				m_mode = GL_RGBA;
				break;
			case 3:
				m_mode = GL_RGB;
				break;
			default:
				m_mode = GL_RGB;
				break;
		}
		glGenTextures(1,&mId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,mId);
		glTexImage2D(GL_TEXTURE_2D,0,m_mode,m_width,m_height,0,m_mode,GL_UNSIGNED_BYTE,data);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wrapMode);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapMode);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filter);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filter);

		glBindTexture(GL_TEXTURE_2D,0);
	}
	Texture2D::~Texture2D() {
		glDeleteTextures(1,&mId);
	}
	Texture2D::Texture2D(Texture2D&& texture_2d) {
		mId = texture_2d.mId;
		texture_2d.mId = 0;
		m_mode = texture_2d.m_mode;
		m_width = texture_2d.m_width;
		m_height = texture_2d.m_height;
	}
	Texture2D &Texture2D::operator=(Texture2D &&texture_2d) {
		glDeleteTextures(1,&mId);
		mId = texture_2d.mId;
		texture_2d.mId = 0;
		m_mode = texture_2d.m_mode;
		m_width = texture_2d.m_width;
		m_height = texture_2d.m_height;
		return *this;
	}
	void Texture2D::bind() const {
		glBindTexture(GL_TEXTURE_2D,mId);
	}
}
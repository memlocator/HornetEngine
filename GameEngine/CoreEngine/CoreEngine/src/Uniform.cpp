#include "Uniform.h"

#include "Graphics.h"
#include "Texture.h"

UniformBase::UniformBase(const std::string& name, const std::string& type, ShaderProgram* program) : Name(name), Type(type), Program(program)
{
	Handle = program->RegisterUniform(this); CheckGLErrors();
}

GLint UniformBase::GetHandle() const
{
	return Handle;
}

const std::string& UniformBase::GetName() const
{
	return Name;
}

void UniformBase::Validate()
{
	//if (ShaderProgram::GetCurrentProgram() != Program)
	//	throw "Attempt to set '" + Program->GetName() + "." + Name + "' while program '" + ShaderProgram::GetCurrentProgram()->GetName() + "' is active";
}

namespace GLSL
{
	bool Bool::Set(bool value)
	{
		Validate();

		if (CurrentValue != value || !Initialized)
		{
			CurrentValue = value;
			Initialized = true;

			glUniform1i(GetHandle(), int(value)); CheckGLErrors();
		}

		return true;
	}

	bool Int::Set(int value)
	{
		Validate();

		glUniform1i(GetHandle(), value); CheckGLErrors();

		return true;
	}

	bool Float::Set(float value)
	{
		Validate();

		glUniform1f(GetHandle(), value); CheckGLErrors();

		return true;
	}

	bool Float::Set(double value)
	{
		return Set((float)value);
	}

	bool Vec2::Set(const Vector3& vector)
	{
		Validate();

		return Set(vector.X, vector.Y);
	}

	bool Vec2::Set(float x, float y)
	{
		Validate();

		glUniform2f(GetHandle(), x, y); CheckGLErrors();

		return true;
	}

	bool Vec2::Set(double x, double y)
	{
		return Set((float)x, (float)y);
	}

	bool Vec3::Set(const Vector3& vector)
	{
		Validate();

		return Set(vector.X, vector.Y, vector.Z);
	}

	bool Vec3::Set(const Color4& color)
	{
		Validate();

		return Set(color.R, color.G, color.B);
	}

	bool Vec3::Set(float x, float y, float z)
	{
		Validate();

		if (x != CurrentValues.X || y != CurrentValues.Y || z != CurrentValues.Z)
		{
			CurrentValues.Set(x, y, z);

			glUniform3f(GetHandle(), x, y, z); CheckGLErrors();
		}

		return true;
	}

	bool Vec3::Set(double x, double y, double z)
	{
		return Set((float)x, (float)y, (float)z);
	}

	bool Vec3::Set(unsigned int color)
	{
		Validate();

		Color4 rgb(color);

		return Set(rgb.R, rgb.G, rgb.B);
	}

	bool Vec4::Set(const Vector3& vector)
	{
		Validate();

		return Set(vector.X, vector.Y, vector.Z, vector.W);
	}

	bool Vec4::Set(const Color4& color)
	{
		Validate();

		return Set(color.R, color.G, color.B, color.A);
	}

	bool Vec4::Set(float x, float y, float z, float w)
	{
		Validate();

		if (x != CurrentValues.X || y != CurrentValues.Y || z != CurrentValues.Z || w != CurrentValues.W)
		{
			CurrentValues.Set(x, y, z, w);

			glUniform4f(GetHandle(), x, y, z, w); CheckGLErrors();
		}

		return true;
	}

	bool Vec4::Set(double x, double y, double z, double w)
	{
		return Set((float)x, (float)y, (float)z, (float)w);
	}

	bool Vec4::Set(unsigned int color)
	{
		Validate();

		return Set(Color4(color));
	}

	template <typename T>
	void sendMatrix(GLint handle, const T*);

	template <>
	void sendMatrix<float>(GLint handle, const float* matrix)
	{
		glUniformMatrix4fv(handle, 1, GL_TRUE, matrix); CheckGLErrors();
	}

	template <>
	void sendMatrix<double>(GLint handle, const double* matrix)
	{
		float mat[16];

		for (int i = 0; i < 16; ++i) mat[i] = (float)matrix[i];

		glUniformMatrix4fv(handle, 1, GL_TRUE, mat); CheckGLErrors();
	}

	bool Matrix::Set(const Matrix4& matrix)
	{
		Validate();

		sendMatrix(GetHandle(), &matrix.Data[0][0]); CheckGLErrors();

		return true;
	}

	int Sampler2D::BoundSampler = -1;
	typename Sampler2D::SamplerVector Sampler2D::Samplers = SamplerVector();

	bool Sampler2D::Set(GLuint texture, int sampler)
	{
		Validate();

		if (int(Samplers.size()) <= sampler || !Samplers[sampler].BoundTexture || Samplers[sampler].CurrentTextureID != texture)
		{
			while (int(Samplers.size()) <= sampler)
				Samplers.push_back(SamplerData());

			SamplerData& samplerData = Samplers[sampler];

			samplerData.BoundTexture = true;
			samplerData.CurrentTextureID = texture;

			if (BoundSampler != sampler)
			{
				BoundSampler = sampler;
				glActiveTexture(GL_TEXTURE0 + sampler); CheckGLErrors();
			}

			glBindTexture(GL_TEXTURE_2D, texture); CheckGLErrors();
		}

		if (CurrentSampler != sampler)
		{
			CurrentSampler = sampler;

			glUniform1i(GetHandle(), sampler); CheckGLErrors();
		}

		return true;
	}

	bool Sampler2D::Set(const std::shared_ptr<GraphicsEngine::Texture>& texture, int sampler)
	{
		Validate();

		if (texture != nullptr)
			return Set(texture->GetTextureID(), sampler);

		return true;
	}

	bool IntArray::Set(const int* values, int size)
	{
		Validate();

		glUniform1iv(GetHandle(), size, values); CheckGLErrors();

		return true;
	}

	bool FloatArray::Set(const float* values, int size)
	{
		Validate();

		glUniform1fv(GetHandle(), size, values); CheckGLErrors();

		return true;
	}

	bool FloatArray::Set(const double* values, int size)
	{
		if (size < 16)
		{
			float fvalues[16];

			for (int i = 0; i < size; ++i)
				fvalues[i] = (float)values[i];

			Set(fvalues, size);
		}
		else
		{
			float* fvalues = new float[size];

			for (int i = 0; i < size; ++i)
				fvalues[i] = (float)values[i];

			Set(fvalues, size);

			delete[] fvalues;
		}

		return true;
	}

	namespace
	{
		typedef std::vector<float> FloatVector;

		FloatVector buffer;
	}

	bool Vec2Array::Set(const float* data, int size)
	{
		Validate();

		glUniform2fv(GetHandle(), size, data); CheckGLErrors();

		return true;
	}

	bool Vec2Array::Set(const double* data, int size)
	{
		if (size <= 16)
		{
			float fdata[16];

			for (int i = 0; i < size; ++i)
				fdata[i] = (float)data[i];

			return Set(fdata, size);
		}
		else
		{
			float* fdata = new float[size];

			for (int i = 0; i < size; ++i)
				fdata[i] = (float)data[i];

			Set(fdata, size);

			delete[] fdata;

			return true;
		}
	}

	bool Vec2Array::Set(const Vector3* vector, int size)
	{
		Validate();

		buffer.resize(size * 2);

		for (int i = 0; i < size; ++i)
		{
			buffer[2 * i] = (float)vector->X;
			buffer[2 * i + 1] = (float)vector->Y;
		}

		return Set(buffer.data(), size);
	}

	bool Vec3Array::Set(const float* data, int size)
	{
		Validate();

		glUniform3fv(GetHandle(), size, data); CheckGLErrors();

		return true;
	}

	bool Vec3Array::Set(const double* data, int size)
	{
		if (size <= 16)
		{
			float fdata[16];

			for (int i = 0; i < size; ++i)
				fdata[i] = (float)data[i];

			Set(fdata, size);
		}
		else
		{
			float* fdata = new float[size];

			for (int i = 0; i < size; ++i)
				fdata[i] = (float)data[i];

			Set(fdata, size);

			delete[] fdata;
		}

		return true;
	}

	bool Vec3Array::Set(const Vector3* vector, int size)
	{
		Validate();

		buffer.resize(size * 3);

		for (int i = 0; i < size; ++i)
		{
			buffer[3 * i] = (float)vector->X;
			buffer[3 * i + 1] = (float)vector->Y;
			buffer[3 * i + 2] = (float)vector->Z;
		}

		return Set(buffer.data(), size);
	}
}

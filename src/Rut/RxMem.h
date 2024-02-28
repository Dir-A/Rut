#pragma once
#include <cassert>
#include <concepts>
#include <type_traits>
#include <memory>
#include <string>
#include <utility>
#include <filesystem>


namespace Rut::RxMem
{
	class Viewer
	{
	private:
		size_t m_nPos = 0;
		const uint8_t* m_pData = nullptr;

	public:
		Viewer(const void* pData);
		template<class Size_T> Viewer(const void* pData, Size_T nSkip);

	public:
		void Rewind();
		template<class Size_T> void Skip(Size_T nBytes);
		template<class Ptr_T> auto CurPtr() const;
		template<class Data_T> auto Read();
		template<class Size_T> void Read(void* pData, Size_T nBytes);
		template<class Data_T> void Write(const Data_T& rfData);
		template<class Size_T> void Write(const void* pData, Size_T nBytes);
		template<class Data_T> Viewer& operator>>(Data_T& rfData);
		template<class Data_T> Viewer& operator<<(const Data_T& rfData);

	};

	inline Viewer::Viewer(const void* pData) : m_pData((const uint8_t*)pData)
	{

	}

	template<class Size_T> inline Viewer::Viewer(const void* pData, Size_T nSkip) : m_pData((const uint8_t*)pData), m_nPos((size_t)nSkip)
	{

	}

	inline void Viewer::Rewind()
	{
		m_nPos = 0;
	}

	template<class Size_T> inline void Viewer::Skip(Size_T nBytes)
	{
		m_nPos += (Size_T)nBytes;
	}

	template<class Ptr_T> inline auto Viewer::CurPtr() const
	{
		if constexpr (std::is_pointer_v<Ptr_T>)
		{
			return (Ptr_T)(m_pData + m_nPos);
		}
		else
		{
			return (Ptr_T*)(m_pData + m_nPos);
		}
	}

	template<class Data_T> inline auto Viewer::Read()
	{
		Data_T val;
		this->Read(&val, sizeof(val));
		return val;
	}

	template<class Size_T> inline void Viewer::Read(void* pData, Size_T nBytes)
	{
		std::memcpy(pData, this->CurPtr<void>(), nBytes);
		m_nPos += nBytes;
	}

	template<class Data_T> inline void Viewer::Write(const Data_T& rfData)
	{
		this->Write(&rfData, sizeof(rfData));
	}

	template<class Size_T> inline void Viewer::Write(const void* pData, Size_T nBytes)
	{
		std::memcpy(this->CurPtr<void>(), pData, nBytes);
		m_nPos += nBytes;
	}

	template<class Data_T> inline Viewer& Viewer::operator>>(Data_T& rfData)
	{
		rfData = this->Read<Data_T>();
		return *this;
	}

	template<class Data_T> inline Viewer& Viewer::operator<<(const Data_T& rfData)
	{
		this->Write<Data_T>(rfData);
		return *this;
	}
}

namespace Rut::RxMem
{
	constexpr size_t AUTO_MEM_AUTO_SIZE = -1;

	template <class T> concept FileStreamType = requires (T tFs, size_t nOffset, size_t nMode, void* pData, size_t nSize)
	{
		{ tFs.SetPos(nOffset, nMode) } -> std::same_as<size_t>;
		{ tFs.Write(pData, nSize) } -> std::same_as<size_t>;
	};

	class Auto
	{
	private:
		size_t m_uiMemSize;
		size_t m_uiMaxSize;
		std::unique_ptr<uint8_t[]> m_upMemData;

	public:
		Auto();
		Auto(std::initializer_list<Auto> lsOBJ);
		Auto(size_t nSize);
		Auto(const Auto& buffer);
		Auto(Auto&& buffer) noexcept;
		Auto(const std::filesystem::path& phPath, size_t szFile = AUTO_MEM_AUTO_SIZE);
		~Auto();

		Auto& Copy(const Auto& buffer);
		Auto& Move(Auto&& buffer) noexcept;
		Auto& Append(const Auto& rfMem);

		uint8_t operator[] (size_t tSize) noexcept;
		Auto& operator=(Auto&& rfAutoMem) noexcept;
		Auto& operator=(const Auto& rfAutoMem);
		Auto& operator+(const Auto& rfAutoMem);

		uint8_t* begin() const noexcept;
		uint8_t* end() const noexcept;

	public:
		void SaveData(const std::filesystem::path& phPath);
		void LoadFile(const std::filesystem::path& phPath, size_t nSize = AUTO_MEM_AUTO_SIZE);

	public:
		template <FileStreamType T> void ReadData(T&& rfFS, size_t nSize = AUTO_MEM_AUTO_SIZE, size_t nPos = AUTO_MEM_AUTO_SIZE);
		template <FileStreamType T> void WriteData(T&& rfFS, size_t nPos = AUTO_MEM_AUTO_SIZE);

	public:
		template<class T = uint8_t*> T GetPtr() const noexcept;
		template<class T = size_t> constexpr T GetSize() const noexcept;
		Viewer GetView();
		void SetSize(size_t uiNewSize, bool isCopy = false);
	};

	template<class T> T Auto::GetPtr() const noexcept
	{
		return (T)m_upMemData.get();
	}

	template<class T> constexpr T Auto::GetSize() const noexcept
	{
		return (T)m_uiMemSize;
	}

	template <FileStreamType T> void Auto::ReadData(T&& rfFS, size_t nSize, size_t nPos)
	{
		if (nSize != AUTO_MEM_AUTO_SIZE) { this->SetSize(nSize); }
		if (nPos != AUTO_MEM_AUTO_SIZE) { rfFS.SetPos(nPos); }
		rfFS.Read(this->GetPtr(), this->GetSize());
	}

	template <FileStreamType T> void Auto::WriteData(T&& rfFS, size_t nPos)
	{
		if (nPos != AUTO_MEM_AUTO_SIZE) { rfFS.SetPos(nPos); }
		rfFS.Write(this->GetPtr(), this->GetSize());
	}

}
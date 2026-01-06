#pragma once

#ifndef SITEMPLATE_H
#define SITEMPLATE_H



// BE MARKED AS FINISHED
// SITemplate.h 用于实现单例模式
template <typename T>
class SITemplate {

public:
	static T* Instance() {
		// 如果没有实例，则创建一个。有则直接返回已创建的实例
		if (!_Sitemplate) _Sitemplate = new	T();
		return _Sitemplate;
	}

protected:
	SITemplate() = default;
	~SITemplate() = default;
	SITemplate(const SITemplate&) = delete;
	SITemplate& operator=(const SITemplate&) = delete;
	 
private:
	static T* _Sitemplate;
};
template <typename T>
T* SITemplate<T>::_Sitemplate = nullptr;
#endif // !SITEMPLATE_H
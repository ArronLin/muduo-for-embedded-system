#ifndef MUDUOEMB_BASE_UNCOPYABLE_H
#define MUDUOEMB_BASE_UNCOPYABLE_H

namespace muduoEmb
{

class Uncopyable
{
	protected:
		Uncopyable() { }
		~Uncopyable() { }
	private:
		Uncopyable(const Uncopyable&);
		Uncopyable& operator=(const Uncopyable&);
};

}
#endif


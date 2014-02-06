#ifndef MUDUOEMB_BASE_UNCOPYABLE
#define MUDUOEMB_BASE_UNCOPYABLE

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


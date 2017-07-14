#ifndef SZM_FAT_LEAF
#define SZM_FAT_LEAF

#include "QuadTree.hpp"
#include "Geometry.hpp"

#include <stdlib.h>
#include <vector>

template <typename S, class T>
class FatLeaf: QuadTree<S, T>
{
	private:
		std::vector<geo::Frame<T>> frames;
		int level;

	public:
		FatLeaf(int l)
		{
			frames.reserve(100);
			level = l;
		}

		void Insert(S minx, S maxx, S miny, S maxy, T* pE)
		{
			geo::Frame frame;
			frame.minx = minx;
			frame.maxx = maxx;
			frame.miny = miny;
			frame.maxy = maxy;
			frame.entity = pE;
			frames.push_back(frame);
		}
};

#endif

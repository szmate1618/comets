#ifndef SZM_ADAPTIVE_UNBOUNDED_QUAD_TREE
#define SZM_ADAPTIVE_UNBOUNDED_QUAD_TREE

#include "QuadTree.hpp"
#include "..\Geometry\Geometry.hpp"

#include <iostream>

template <typename S, class T>
class AdaptiveUnboundedQuadTree: QuadTree<S, T>
{
	private:
		void CalculateCenter(S minx, S maxx, S miny, S maxy)
		{
			centerx = (minx + maxx) / 2;
			centery = (miny + maxy) / 2;
			for (int i = 0; i < count; i++)
			{
				centerx += (frames[i].minx + frames[i].maxx) / 2;
				centery += (frames[i].miny + frames[i].maxy) / 2;
			}
			centerx /= (count + 1);
			centery /= (count + 1);
		}

		void Split()
		{
			ur = new AdaptiveUnboundedQuadTree(level + 1);
			ul = new AdaptiveUnboundedQuadTree(level + 1);
			ll = new AdaptiveUnboundedQuadTree(level + 1);
			lr = new AdaptiveUnboundedQuadTree(level + 1);
		}

		void InsertIntoDescendants(S minx, S maxx, S miny, S maxy, T* pE)
		{
			if (maxx >= centerx && maxy >= centery)
				ur->Insert(__max(minx, centerx + epsilon), maxx, __max(miny, centery + epsilon), maxy, pE);
			if (minx <= centerx && maxy >= centery)
				ul->Insert(minx, __min(maxx, centerx - epsilon), __max(miny, centery + epsilon), maxy, pE);
			if (minx <= centerx && miny <= centery)
				ll->Insert(minx, __min(maxx, centerx - epsilon), miny, __min(maxy, centery - epsilon), pE);
			if (maxx >= centerx && miny <= centery)
				lr->Insert(__max(minx, centerx + epsilon), maxx, miny, __min(maxy, centery - epsilon), pE);
		}

	public:
		static const int maxcapacity = 10;

		double centerx, centery;
		int level;

		AdaptiveUnboundedQuadTree* ur;
		AdaptiveUnboundedQuadTree* ul;
		AdaptiveUnboundedQuadTree* ll;
		AdaptiveUnboundedQuadTree* lr;

		geo::Frame<S, T> frames[maxcapacity];
		int count;

		AdaptiveUnboundedQuadTree(int l)
		{
			count = 0;
			level = l;
			ur = NULL;
			ul = NULL;
			ll = NULL;
			lr = NULL;
		}

		void Insert(S minx, S maxx, S miny, S maxy, T* pE)
		{
			if (count == maxcapacity)
			{
				CalculateCenter(minx, maxx, miny, maxy);
				count = 0;
				Split();
				for (int i = 0; i < maxcapacity; i++)
				{				
					InsertIntoDescendants(frames[i].minx, frames[i].maxx, frames[i].miny, frames[i].maxy, frames[i].entity);
				}
			}
			if (ur != NULL)
			{
				InsertIntoDescendants(minx, maxx, miny, maxy, pE);
			}
			else
			{
				//frames[count] = {minx, maxx, miny, maxy, pE};
				frames[count].minx = minx;
				frames[count].maxx = maxx;
				frames[count].miny = miny;
				frames[count].maxy = maxy;
				frames[count].entity = pE;
				count++;
			}
		}

		~AdaptiveUnboundedQuadTree()
		{
			delete ur;
			delete ul;
			delete ll;
			delete lr;
		}
};


#endif

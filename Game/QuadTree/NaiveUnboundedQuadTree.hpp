#ifndef SZM_NAIVE_UNBOUNDED_QUAD_TREE
#define SZM_NAIVE_UNBOUNDED_QUAD_TREE

#include "QuadTree.hpp"
#include "Geometry.hpp"

#include <iostream>

template <typename S, class T>
class NaiveUnboundedQuadTree: QuadTree<S, T>
{
	private:
		void Split()
		{
			ur = new NaiveUnboundedQuadTree(centerx + size / 4, centery + size / 4, size / 2, level + 1);
			ul = new NaiveUnboundedQuadTree(centerx - size / 4, centery + size / 4, size / 2, level + 1);
			ll = new NaiveUnboundedQuadTree(centerx - size / 4, centery - size / 4, size / 2, level + 1);
			lr = new NaiveUnboundedQuadTree(centerx + size / 4, centery - size / 4, size / 2, level + 1);
		}

	public:
		static const int maxcapacity = 10;

		double centerx, centery, size;
		int level;

		NaiveUnboundedQuadTree* ur;
		NaiveUnboundedQuadTree* ul;
		NaiveUnboundedQuadTree* ll;
		NaiveUnboundedQuadTree* lr;

		geo::Frame<S, T> frames[maxcapacity];
		int count;

		NaiveUnboundedQuadTree(S x, S y, S s, int l)
		{
			//std::cout << x << " " << y << " " << s << " " << " " << l << std::endl;
			centerx = x;
			centery = y;
			size = s;
			count = 0;
			level = l;
			ur = NULL;
			ul = NULL;
			ll = NULL;
			lr = NULL;
		}
		
		void InsertIntoDescendants(double minx, double maxx, double miny, double maxy, T* pE)
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

		void Insert(double minx, double maxx, double miny, double maxy, T* pE)
		{
			if (count == maxcapacity)
			{
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
				//std::cout << "inserted " << minx << " " << maxx << " " << miny << " " << maxy << " at level " << level << std::endl;
			}
		}

		~NaiveUnboundedQuadTree()
		{
			delete ur;
			delete ul;
			delete ll;
			delete lr;
		}
};


#endif

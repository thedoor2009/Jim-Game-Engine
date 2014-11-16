#ifndef BUFFER_NODE_CLASS
#define BUFFER_LNODE_CLASS

namespace JimEngine
{
	template <class __Type__>
	class BufferNode
	{
		public:
			BufferNode()
			{

			}
			~BufferNode()
			{

			}
			__Type__  data;
			BufferNode<__Type__> *next;
	};
}
#endif
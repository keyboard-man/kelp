#include "base_query_interface.ice"
module kelp
{
	interface web2kcn
	{
		BinData Query(string uuid, string serName, string param);
	};
};

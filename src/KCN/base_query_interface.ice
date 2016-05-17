module kelp
{
	sequence<byte> BinData;

	interface QueryInterface
	{
		BinData Foo(string str);
	};
};

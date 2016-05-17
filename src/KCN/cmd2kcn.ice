module kelp
{
    interface cmd2kcn
    {
        //set configuration for uuid node 
        bool setNodeConfig(string uuid, string key, string value);
        //set configuration for self
        bool setSelfConfig(string key, string value);
        //delete configuration for uuid node
        bool delNodeConfig(string uuid, string key);
        //delete configuration for self
        bool delSelfConfig(string key);


        //TODO: add more function to allow use to change the configure of node
    };
};

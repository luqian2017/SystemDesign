这题就是模拟一个大文件的分块和组装。

有一个地方要注意： 
当fileSize < chunkSize时，numOfChunk仍然要设为1。 

可以用以下技巧:

int numOfChunks = (content.size() + chunkSize - 1) / chunkSize; 

也可以用 

int numOfChunks = (content.size() - 1) / chunkSize + 1;

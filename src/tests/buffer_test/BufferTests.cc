#include <gtest/gtest.h>
#include <tiredis/UnboundedBuffer.h>
#include <tiredis/AsyncBuffer.h>
#include <iostream>
#include <limits>

TEST(UnboundedBufferTests, UnboundedBuffer) {
    UnboundedBuffer buf;
    std::size_t ret = buf.PushData("hello", 5);
    ASSERT_EQ(ret, 5);
    char tmp[10];
    ret = buf.PeekData(tmp, sizeof(tmp));
    ASSERT_EQ(ret, 5);
    ASSERT_EQ(tmp[0], 'h');
    ASSERT_TRUE(buf.IsEmpty());

    ret = buf.PushData("world", 5);
    ASSERT_EQ(ret, 5);
    ret = buf.PushData("abcde", 5);
    ASSERT_EQ(ret, 5);
    ret = buf.PeekData(tmp, 5);
    ASSERT_EQ(tmp[0], 'w');

    buf.Clear();
    buf.Shrink();

    ret = buf.PeekData(tmp, 5);
    if (ret == 5)
    {
        ASSERT_EQ(tmp[0], 'a');
        ASSERT_EQ(tmp[1], 'b');
    }
    buf.Shrink();
}

TEST(AsyncBufferTests, AsyncBuffer) {
    AsyncBuffer asbuf;
    asbuf.Write("hello", 5);
    BufferSequence bf;
    asbuf.ProcessBuffer(bf);
    ASSERT_EQ(bf.count, 1);
    std::string data = std::string(static_cast<char *>(bf.buffers[0].iov_base));
    ASSERT_EQ(data, "hello");
}

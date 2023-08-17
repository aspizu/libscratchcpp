#include <scratchcpp/inputvalue.h>
#include <scratchcpp/block.h>
#include <scratchcpp/broadcast.h>
#include <scratchcpp/variable.h>
#include <scratchcpp/list.h>

#include "../common.h"

using namespace libscratchcpp;

TEST(InputValueTest, Constructors)
{
    InputValue value1;
    ASSERT_EQ(value1.type(), InputValue::Type::Number);

    InputValue value2(InputValue::Type::String);
    ASSERT_EQ(value2.type(), InputValue::Type::String);
}

TEST(InputTest, Type)
{
    InputValue value;

    value.setType(InputValue::Type::Color);
    ASSERT_EQ(value.type(), InputValue::Type::Color);
}

TEST(InputTest, Value)
{
    InputValue value;
    ASSERT_EQ(value.value(), Value());

    value.setValue("test");
    ASSERT_EQ(value.value().toString(), "test");
}

TEST(InputTest, ValueBlock)
{
    InputValue value;
    ASSERT_EQ(value.valueBlock(), nullptr);
    ASSERT_EQ(value.valueBlockId(), "");

    auto block = std::make_shared<Block>("abc", "");
    value.setValueBlock(block);
    ASSERT_EQ(value.valueBlock(), block);
    ASSERT_EQ(value.valueBlockId(), "abc");

    value.setValueBlock(nullptr);
    ASSERT_EQ(value.valueBlock(), nullptr);
    ASSERT_EQ(value.valueBlockId(), "");

    value.setValueBlockId("hello");
    ASSERT_EQ(value.valueBlockId(), "hello");
    ASSERT_EQ(value.valueBlock(), nullptr);
}

TEST(InputTest, ValuePtr)
{
    InputValue value1;
    ASSERT_EQ(value1.valuePtr(), nullptr);
    ASSERT_EQ(value1.valueId(), "");

    auto broadcast = std::make_shared<Broadcast>("abc", "");
    value1.setValuePtr(broadcast);
    ASSERT_EQ(value1.valuePtr(), broadcast);
    ASSERT_EQ(value1.valueId(), "abc");
    ASSERT_EQ(value1.type(), InputValue::Type::Broadcast);

    auto variable = std::make_shared<Variable>("def", "");
    value1.setValuePtr(variable);
    ASSERT_EQ(value1.valuePtr(), variable);
    ASSERT_EQ(value1.valueId(), "def");
    ASSERT_EQ(value1.type(), InputValue::Type::Variable);

    auto list = std::make_shared<List>("ghi", "");
    value1.setValuePtr(list);
    ASSERT_EQ(value1.valuePtr(), list);
    ASSERT_EQ(value1.valueId(), "ghi");
    ASSERT_EQ(value1.type(), InputValue::Type::List);

    auto block = std::make_shared<Block>("jkl", "");
    value1.setValuePtr(block);
    ASSERT_EQ(value1.valuePtr(), nullptr);
    ASSERT_EQ(value1.valueId(), "");
    ASSERT_EQ(value1.type(), InputValue::Type::List);

    value1.setValuePtr(nullptr);
    ASSERT_EQ(value1.valuePtr(), nullptr);
    ASSERT_EQ(value1.valueId(), "");
    ASSERT_EQ(value1.type(), InputValue::Type::List);

    InputValue value2(InputValue::Type::Integer);

    value2.setValuePtr(block);
    ASSERT_EQ(value2.valuePtr(), nullptr);
    ASSERT_EQ(value1.valueId(), "");
    ASSERT_EQ(value2.type(), InputValue::Type::Integer);

    value2.setValuePtr(variable);
    value2.setValueId("hello");
    ASSERT_EQ(value2.valuePtr(), nullptr);
    ASSERT_EQ(value2.valueId(), "hello");
    ASSERT_EQ(value2.type(), InputValue::Type::Variable);
}

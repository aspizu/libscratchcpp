#include <scratchcpp/stage.h>
#include <scratchcpp/costume.h>
#include <enginemock.h>
#include <graphicseffectmock.h>
#include <stagehandlermock.h>

#include "../common.h"

using namespace libscratchcpp;

TEST(StageTest, IsStage)
{
    Stage stage;
    ASSERT_TRUE(stage.isStage());
}

TEST(SpriteTest, Interface)
{
    Stage stage;
    ASSERT_EQ(stage.getInterface(), nullptr);

    StageHandlerMock handler;
    EXPECT_CALL(handler, init);
    stage.setInterface(&handler);
    ASSERT_EQ(stage.getInterface(), &handler);
}

TEST(SpriteTest, CostumeIndex)
{
    Stage stage;
    EngineMock engine;
    stage.setEngine(&engine);
    EXPECT_CALL(engine, requestRedraw()).Times(2);

    auto c1 = std::make_shared<Costume>("", "", "");
    auto c2 = std::make_shared<Costume>("", "", "");
    stage.addCostume(c1);
    stage.addCostume(c2);

    stage.setCostumeIndex(0);
    ASSERT_EQ(stage.costumeIndex(), 0);

    stage.setCostumeIndex(1);
    ASSERT_EQ(stage.costumeIndex(), 1);
}

TEST(StageTest, Tempo)
{
    Stage stage;
    ASSERT_EQ(stage.tempo(), 60);
    stage.setTempo(120);
    ASSERT_EQ(stage.tempo(), 120);
}

TEST(StageTest, VideoState)
{
    Stage stage;
    ASSERT_EQ(stage.videoState(), Stage::VideoState::Off); // default
    ASSERT_EQ(stage.videoStateStr(), "off");

    stage.setVideoState(Stage::VideoState::On);
    ASSERT_EQ(stage.videoState(), Stage::VideoState::On);
    ASSERT_EQ(stage.videoStateStr(), "on");

    stage.setVideoState(Stage::VideoState::OnFlipped);
    ASSERT_EQ(stage.videoState(), Stage::VideoState::OnFlipped);
    ASSERT_EQ(stage.videoStateStr(), "on-flipped");

    stage.setVideoState(Stage::VideoState::Off);
    ASSERT_EQ(stage.videoState(), Stage::VideoState::Off);
    ASSERT_EQ(stage.videoStateStr(), "off");

    stage.setVideoState("invalid");
    ASSERT_EQ(stage.videoState(), Stage::VideoState::Off); // shouldn't change
    ASSERT_EQ(stage.videoStateStr(), "off");

    stage.setVideoState("on");
    ASSERT_EQ(stage.videoState(), Stage::VideoState::On);
    ASSERT_EQ(stage.videoStateStr(), "on");

    stage.setVideoState("on-flipped");
    ASSERT_EQ(stage.videoState(), Stage::VideoState::OnFlipped);
    ASSERT_EQ(stage.videoStateStr(), "on-flipped");

    stage.setVideoState("off");
    ASSERT_EQ(stage.videoState(), Stage::VideoState::Off);
    ASSERT_EQ(stage.videoStateStr(), "off");

    stage.setVideoState(std::string("invalid"));
    ASSERT_EQ(stage.videoState(), Stage::VideoState::Off); // shouldn't change
    ASSERT_EQ(stage.videoStateStr(), "off");

    stage.setVideoState(std::string("on"));
    ASSERT_EQ(stage.videoState(), Stage::VideoState::On);
    ASSERT_EQ(stage.videoStateStr(), "on");

    stage.setVideoState(std::string("on-flipped"));
    ASSERT_EQ(stage.videoState(), Stage::VideoState::OnFlipped);
    ASSERT_EQ(stage.videoStateStr(), "on-flipped");

    stage.setVideoState(std::string("off"));
    ASSERT_EQ(stage.videoState(), Stage::VideoState::Off);
    ASSERT_EQ(stage.videoStateStr(), "off");
}

TEST(StageTest, VideoTransparency)
{
    Stage stage;
    ASSERT_EQ(stage.videoTransparency(), 50);
    stage.setVideoTransparency(100);
    ASSERT_EQ(stage.videoTransparency(), 100);
}

TEST(StageTest, TextToSpeechLanguage)
{
    Stage stage;
    ASSERT_EQ(stage.textToSpeechLanguage(), "");
    stage.setTextToSpeechLanguage("English");
    ASSERT_EQ(stage.textToSpeechLanguage(), "English");
}

TEST(StageTest, DefaultBoundingRect)
{
    Stage stage;
    Rect rect = stage.boundingRect();
    ASSERT_EQ(rect.left(), 0);
    ASSERT_EQ(rect.top(), 0);
    ASSERT_EQ(rect.right(), 0);
    ASSERT_EQ(rect.bottom(), 0);
}

TEST(StageTest, DefaultFastBoundingRect)
{
    Stage stage;
    Rect rect = stage.fastBoundingRect();
    ASSERT_EQ(rect.left(), 0);
    ASSERT_EQ(rect.top(), 0);
    ASSERT_EQ(rect.right(), 0);
    ASSERT_EQ(rect.bottom(), 0);
}

TEST(StageTest, GraphicsEffects)
{
    Stage stage;

    EngineMock engine;
    stage.setEngine(&engine);
    EXPECT_CALL(engine, requestRedraw()).Times(3);

    GraphicsEffectMock effect1, effect2;
    stage.setGraphicsEffectValue(&effect1, 48.21);
    ASSERT_EQ(stage.graphicsEffectValue(&effect1), 48.21);
    ASSERT_EQ(stage.graphicsEffectValue(&effect2), 0);

    stage.setGraphicsEffectValue(&effect2, -107.08);
    ASSERT_EQ(stage.graphicsEffectValue(&effect1), 48.21);
    ASSERT_EQ(stage.graphicsEffectValue(&effect2), -107.08);

    stage.clearGraphicsEffects();
    ASSERT_EQ(stage.graphicsEffectValue(&effect1), 0);
    ASSERT_EQ(stage.graphicsEffectValue(&effect2), 0);
}

TEST(StageTest, BubbleType)
{
    Stage stage;
    ASSERT_EQ(stage.bubbleType(), Target::BubbleType::Say);

    stage.setBubbleType(Target::BubbleType::Think);
    ASSERT_EQ(stage.bubbleType(), Target::BubbleType::Think);

    stage.setBubbleType(Target::BubbleType::Say);
    ASSERT_EQ(stage.bubbleType(), Target::BubbleType::Say);
}

TEST(StageTest, BubbleText)
{
    Stage stage;
    ASSERT_TRUE(stage.bubbleText().empty());

    stage.setBubbleText("hello");
    ASSERT_EQ(stage.bubbleText(), "hello");

    stage.setBubbleText("world");
    ASSERT_EQ(stage.bubbleText(), "world");
}

TEST(StageTest, LayerOrder)
{
    Stage stage;
    ASSERT_EQ(stage.layerOrder(), 0);
    stage.setLayerOrder(2);
    ASSERT_EQ(stage.layerOrder(), 2);
}

#include <gtest/gtest.h>
#include "NPC.h"
#include "NPCFactory.h"
#include "DungeonEditor.h"

// Тест 1: Проверка создания Thief через фабрику
TEST(NPCFactoryTest, CreateThief) {
    auto thief = NPCFactory::createNPC("Thief", "Thief1", 100, 100);
    ASSERT_NE(thief, nullptr);
    EXPECT_EQ(thief->getType(), "Thief");
    EXPECT_EQ(thief->getName(), "Thief1");
    EXPECT_EQ(thief->getX(), 100);
    EXPECT_EQ(thief->getY(), 100);
}

// Тест 2: Проверка создания Orc через фабрику
TEST(NPCFactoryTest, CreateOrc) {
    auto orc = NPCFactory::createNPC("Orc", "Orc1", 200, 200);
    ASSERT_NE(orc, nullptr);
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(orc->getName(), "Orc1");
    EXPECT_EQ(orc->getX(), 200);
    EXPECT_EQ(orc->getY(), 200);
}

// Тест 3: Проверка создания Werewolf через фабрику
TEST(NPCFactoryTest, CreateWerewolf) {
    auto werewolf = NPCFactory::createNPC("Werewolf", "Wolf1", 300, 300);
    ASSERT_NE(werewolf, nullptr);
    EXPECT_EQ(werewolf->getType(), "Werewolf");
    EXPECT_EQ(werewolf->getName(), "Wolf1");
    EXPECT_EQ(werewolf->getX(), 300);
    EXPECT_EQ(werewolf->getY(), 300);
}

// Тест 4: Проверка создания NPC с некорректным типом
TEST(NPCFactoryTest, CreateInvalidNPC) {
    auto invalidNPC = NPCFactory::createNPC("UnknownType", "Invalid1", 0, 0);
    ASSERT_EQ(invalidNPC, nullptr);
}

// Тест 5: Проверка, что Thief может сражаться на корректной дистанции
TEST(NPCTest, ThiefCanFightInRange) {
    auto thief = NPCFactory::createNPC("Thief", "Thief1", 100, 100);
    auto werewolf = NPCFactory::createNPC("Werewolf", "Wolf1", 110, 110);
    EXPECT_TRUE(thief->canFight(*werewolf, 20)); // Дистанция = 14
}

// Тест 6: Проверка, что Thief не может сражаться вне диапазона
TEST(NPCTest, ThiefCannotFightOutOfRange) {
    auto thief = NPCFactory::createNPC("Thief", "Thief1", 100, 100);
    auto werewolf = NPCFactory::createNPC("Werewolf", "Wolf1", 200, 200);
    EXPECT_FALSE(thief->canFight(*werewolf, 50)); // Дистанция = 141
}

// Тест 7: Проверка, что Orc убивает Thief
TEST(BattleTest, OrcKillsThief) {
    auto orc = NPCFactory::createNPC("Orc", "Orc1", 200, 200);
    auto thief = NPCFactory::createNPC("Thief", "Thief1", 210, 210); // В пределах расстояния
    ASSERT_TRUE(orc->canFight(*thief, 20));
    orc->fight(*thief);

    EXPECT_TRUE(orc->alive());
    EXPECT_FALSE(thief->alive());
}

// Тест 8: Проверка, что Werewolf убивает Thief
TEST(BattleTest, WerewolfKillsThief) {
    auto werewolf = NPCFactory::createNPC("Werewolf", "Wolf1", 200, 200);
    auto thief = NPCFactory::createNPC("Thief", "Thief1", 210, 210); // В пределах расстояния
    ASSERT_TRUE(werewolf->canFight(*thief, 20));
    werewolf->fight(*thief);

    EXPECT_TRUE(werewolf->alive());
    EXPECT_FALSE(thief->alive());
}

// Тест 9: Проверка, что Thief и Werewolf могут убить друг друга
TEST(BattleTest, ThiefVsWerewolf) {
    auto thief = NPCFactory::createNPC("Thief", "Thief1", 100, 100);
    auto werewolf = NPCFactory::createNPC("Werewolf", "Wolf1", 110, 110); // В пределах расстояния

    ASSERT_TRUE(thief->canFight(*werewolf, 20)); // Дистанция между ними = 14
    thief->fight(*werewolf);

    // Проверяем, что один из них умер
    EXPECT_FALSE(thief->alive() && werewolf->alive());
}

// Тест 10: Проверка, что NPC удаляются после смерти
TEST(BattleTest, RemoveDeadNPCs) {
    DungeonEditor editor;
    editor.addNPC("Thief", "Thief1", 100, 100);
    editor.addNPC("Orc", "Orc1", 200, 200);
    editor.startBattle(150);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    editor.printNPCs();
    std::string result = testing::internal::GetCapturedStdout();

    // Убедимся, что мертвые NPC удалены
    EXPECT_TRUE(result.find("Thief1") == std::string::npos);
}

// Тест 11: Проверка сохранения и загрузки NPC
TEST(DungeonEditorTest, SaveAndLoadNPCs) {
    DungeonEditor editor;
    editor.addNPC("Thief", "Thief1", 100, 100);
    editor.addNPC("Orc", "Orc1", 200, 200);
    editor.saveToFile("test_save.txt");

    DungeonEditor newEditor;
    newEditor.loadFromFile("test_save.txt");

    testing::internal::CaptureStdout();
    newEditor.printNPCs();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Thief1") != std::string::npos);
    EXPECT_TRUE(output.find("Orc1") != std::string::npos);
}

// Тест 12: Проверка начального состояния NPC
TEST(NPCTest, InitialState) {
    auto thief = NPCFactory::createNPC("Thief", "Thief1", 100, 100);
    EXPECT_TRUE(thief->alive());
}

// Тест 13: Проверка работы ConsoleObserver
TEST(ObserverTest, ConsoleObserver) {
    ConsoleObserver observer;

    testing::internal::CaptureStdout();
    observer.update("Test message");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Test message\n");
}

// Тест 14: Проверка работы FileObserver
TEST(ObserverTest, FileObserver) {
    FileObserver observer("test_log.txt");
    observer.update("Test log message");

    std::ifstream file("test_log.txt");
    std::string line;
    std::getline(file, line);

    EXPECT_EQ(line, "Test log message");
    file.close();
}

// Тест 15: Проверка, что Observer корректно уведомляет о событиях
TEST(BattleTest, ObserverNotification) {
    DungeonEditor editor;
    editor.addNPC("Orc", "Orc1", 100, 100);
    editor.addNPC("Thief", "Thief1", 110, 110);

    testing::internal::CaptureStdout();
    editor.startBattle(20);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Orc1 is killing Thief1") != std::string::npos);
    EXPECT_TRUE(output.find("Thief1 was killed by Orc1") != std::string::npos);
}
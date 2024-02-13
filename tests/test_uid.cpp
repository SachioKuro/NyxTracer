#include <gtest/gtest.h>
#include "../src/uid.hpp"

TEST(UID, Init) {
    Nyx::UID uid = Nyx::UID();
    EXPECT_EQ(uid.value, 1);

    Nyx::UID uid2 = Nyx::UID();
    EXPECT_EQ(uid2.value, 2);

    Nyx::UID uid3 = Nyx::UID();
    EXPECT_EQ(uid3.value, 3);
}

TEST(UID, Ordering) {
    Nyx::UID uid = Nyx::UID();
    Nyx::UID uid2 = Nyx::UID();
    Nyx::UID uid3 = Nyx::UID();
    Nyx::UID uid4 = Nyx::UID();

    EXPECT_EQ(uid < uid2, true);
    EXPECT_EQ(uid2 < uid3, true);
    EXPECT_EQ(uid3 < uid4, true);
    EXPECT_EQ(uid < uid4, true);
    EXPECT_EQ(uid2 < uid4, true);
    EXPECT_EQ(uid < uid3, true);

    EXPECT_EQ(uid4 < uid3, false);
    EXPECT_EQ(uid4 < uid2, false);
    EXPECT_EQ(uid4 < uid, false);
    EXPECT_EQ(uid3 < uid2, false);
    EXPECT_EQ(uid3 < uid, false);
    EXPECT_EQ(uid2 < uid, false);

    EXPECT_EQ(uid4 > uid3, true);
    EXPECT_EQ(uid4 > uid2, true);
    EXPECT_EQ(uid4 > uid, true);
    EXPECT_EQ(uid3 > uid2, true);
    EXPECT_EQ(uid3 > uid, true);
    EXPECT_EQ(uid2 > uid, true);

    EXPECT_EQ(uid > uid2, false);
    EXPECT_EQ(uid2 > uid3, false);
    EXPECT_EQ(uid3 > uid4, false);
    EXPECT_EQ(uid > uid4, false);
    EXPECT_EQ(uid2 > uid4, false);
    EXPECT_EQ(uid > uid3, false);
}
#include <gtest/gtest.h>
#include "../src/object.hpp"
#include "../src/sphere.hpp"

TEST(Object, Init) {
    Nyx::UID::reset();

    Nyx::Sphere o = Nyx::Sphere();
    EXPECT_EQ(o.id.value, 1);

    Nyx::Sphere o2 = Nyx::Sphere();
    EXPECT_EQ(o2.id.value, 2);

    Nyx::Sphere o3 = Nyx::Sphere();
    EXPECT_EQ(o3.id.value, 3);

    EXPECT_TRUE(o.id != o2.id);
    EXPECT_TRUE(o.id == o.id);
    EXPECT_TRUE(o2.id != o3.id);
    EXPECT_TRUE(o2.id == o2.id);
    EXPECT_TRUE(o.id != o3.id);
    EXPECT_TRUE(o3.id == o3.id);
}

TEST(Object, Transformation) {
    Nyx::Sphere o = Nyx::Sphere();
    
    EXPECT_EQ(o.transform, Nyx::Transformation::identity());

    Nyx::Transformation t = Nyx::Transformation::identity().translate(2, 3, 4);
    o.set_transform(t);

    EXPECT_EQ(o.transform, t);
    EXPECT_EQ(o.inverse_transform, t.inverse());
    EXPECT_EQ(o.inverse_transpose_transform, t.inverse().transpose());
}

TEST(Object, Material) {
    Nyx::Sphere o = Nyx::Sphere();
    
    EXPECT_EQ(o.material, Nyx::Material());

    Nyx::Material m = Nyx::Material();
    m.color = Nyx::Color(1, 0, 0);
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200;
    o.material = m;

    EXPECT_EQ(o.material, m);
}
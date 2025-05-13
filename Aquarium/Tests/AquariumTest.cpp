/**
 * @file AquariumTest.cpp
 * @author Bilal
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Aquarium.h>
#include <FishBeta.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>
#include <FishNemo.h>

#include <FishAngel.h>
#include <DecorCastle.h>
#include <Fish.h>


using namespace std;




class AquariumTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;

    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
        ASSERT_FALSE(regex_search(xml, wregex(L"<\\?xxml.*\\?>")));

    }


    /**
     *  Populate an aquarium with three Beta fish
     */
    void PopulateThreeBetas(Aquarium *aquarium)
    {

        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);
        fish1->SetSpeed(30,25);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);
        fish2->SetSpeed(10,5);

        auto fish3 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);
        fish3->SetSpeed(5,35);
    }

    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions and speed are  correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedX=\"30\" speedY=\"25\" type=\"beta\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedX=\"10\" speedY=\"5\" type=\"beta\"")));
        ASSERT_TRUE(regex_search(xml, wregex(   L"<item x=\"600\" y=\"100\" speedX=\"5\" speedY=\"35\" type=\"beta\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));


    }

    void PopulateAllTypes(Aquarium *aquarium)
    {

        auto fishBeta = make_shared<FishBeta>(aquarium);
        aquarium->Add(fishBeta);
        fishBeta->SetLocation(100, 200);
        fishBeta->SetSpeed(1,1);

        auto fishAngel = make_shared<FishAngel>(aquarium);
        aquarium->Add(fishAngel);
        fishAngel->SetLocation(400, 400);
        fishAngel->SetSpeed(12,7);

        auto fishNemo = make_shared<FishNemo>(aquarium);
        aquarium->Add(fishNemo);
        fishNemo->SetLocation(600, 100);
        fishNemo->SetSpeed(10,5);

        auto decorCastle = make_shared<DecorCastle>(aquarium);
        aquarium->Add(decorCastle);
        decorCastle->SetLocation(600, 200);

    }

    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

        // Ensure the positions and speed is correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedX=\"1\" speedY=\"1\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedX=\"12\" speedY=\"7\"")));
        ASSERT_TRUE(regex_search(xml, wregex( L"<item x=\"600\" y=\"100\" speedX=\"10\" speedY=\"5\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"200\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"angel\"/><item.* type=\"nemo\"/><item.* type=\"castle\"/></aqua>")));



    }
};

TEST_F(AquariumTest, Construct){
    Aquarium aquarium;
}

TEST_F(AquariumTest, HitTest) {
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
        L"Testing empty aquarium";

    // Creates a fish objects and adds it them to the aquarium
    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);


    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) <<
          L"Testing fish at 100, 200";

    ASSERT_TRUE(aquarium.HitTest(10, 10) == nullptr) <<
        L"Testing where there is no image ";

    ASSERT_FALSE(aquarium.HitTest(100, 200) == nullptr) <<
        L"Testing where there is no image ";

    // Creates a second fish object and adds it to the aquarium
    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish2) <<
        L"Testing second fish at 100, 200";

    ASSERT_FALSE(aquarium.HitTest(100, 200) == fish1) <<
        L"Testing second fish at 100, 200";


}


TEST_F(AquariumTest, Save) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);


    // Test all types

    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);



}

TEST_F(AquariumTest, Clear)
{
    // Create a path to temporary files
    auto path = TempPath();

    auto file4 = path + L"/test4.aqua";

    Aquarium aquarium4;


     PopulateThreeBetas(&aquarium4);
     aquarium4.Save(file4);

     TestThreeBetas(file4);

     aquarium4.Clear();

     aquarium4.Save(file4);

     TestEmpty(file4);

}


TEST_F(AquariumTest, Load) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;
    Aquarium aquarium2;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    aquarium2.Load(file1);
    aquarium2.Save(file1);
    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);

    aquarium2.Load(file3);
    aquarium2.Save(file3);
    TestAllTypes(file3);
}



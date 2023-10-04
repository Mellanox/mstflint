/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// #define USE_BOOST

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#ifdef USE_BOOST
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
namespace fs = boost::filesystem;
#else
#include "filesystem.h"
namespace fs = mstflint::common::filesystem;
#endif

#if 0
#include <ostream>
TEST(filesystem, existsFileVaryPerms) {
  for (int special = 0; special <= 7; ++special) {
    for (int others = 0; others <= 7; ++others) {
      for (int group = 0; group <= 7; ++group) {
        for (int owner = 0; owner <= 7; ++owner) {
          std::ostringstream oss;
          oss << "data/overkill/file-" << special << owner << group << others;
          fs::path p(oss.str());
          ASSERT_TRUE(fs::exists(p));
        }
      }
    }
  }
}

TEST(filesystem, existsFolderVaryPerms) {
  for (int special = 0; special <= 7; ++special) {
    for (int others = 0; others <= 7; ++others) {
      for (int group = 0; group <= 7; ++group) {
        for (int owner = 0; owner <= 7; ++owner) {
          std::ostringstream oss;
          oss << "data/overkill/folder-" << special << owner << group << others;
          fs::path p(oss.str());
          ASSERT_TRUE(fs::exists(p));
        }
      }
    }
  }
}
#endif

TEST(exists, RegularFile) {
  fs::path p("data/regular-file");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, RegularFolder) {
  fs::path p("data/regular-folder");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, SoftLinkToFile) {
  fs::path p("data/soft-link-to-file");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, SoftLinkToSoftLinkToFile) {
  fs::path p("data/soft-link-to-soft-link-to-file");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, SoftLinkToFileAbsolutePath) {
  fs::path p("data/soft-link-to-file-absolute-path");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, SoftLinkToFolder) {
  fs::path p("data/soft-link-to-folder");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, SoftLinkToSoftLinkToFolder) {
  fs::path p("data/soft-link-to-soft-link-to-folder");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, SoftLinkToFolderAbsolutePath) {
  fs::path p("data/soft-link-to-folder-absolute-path");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, DeadSoftLink) {
  fs::path p("data/dead-soft-link");
  // boost::filesystem::exists returns false on dead soft links, so we are
  ASSERT_FALSE(fs::exists(p));
}

TEST(exists, HardLinkToFile) {
  fs::path p("data/hard-link-to-file");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, HardLinkToFileAbsolutePath) {
  fs::path p("data/hard-link-to-file-absolute-path");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, Negative) {
  fs::path p("DoesNotExist");
  ASSERT_FALSE(fs::exists(p));
}

TEST(exists, FileWithSpaceInTheName) {
  fs::path p("data/file with spaces in the name");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, FolderWithSpaceInTheName) {
  fs::path p("data/folder with spaces in the name");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, FileUnderFolderWithNoReadPermissions) {
  fs::path p("data/folder-0311/file");
  ASSERT_TRUE(fs::exists(p));
}

TEST(exists, FolderUnderFolderWithNoReadPermissions) {
  fs::path p("data/folder-0311/folder");
  ASSERT_TRUE(fs::exists(p));
}

TEST(is_regular_file, RegularFile) {
  fs::path p("data/regular-file");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, RegularFolder) {
  fs::path p("data/regular-folder");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_regular_file, SoftLinkToFile) {
  fs::path p("data/soft-link-to-file");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, SoftLinkToSoftLinkToFile) {
  fs::path p("data/soft-link-to-soft-link-to-file");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, SoftLinkToFileAbsolutePath) {
  fs::path p("data/soft-link-to-file-absolute-path");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, SoftLinkToFolder) {
  fs::path p("data/soft-link-to-folder");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_regular_file, SoftLinkToSoftLinkToFolder) {
  fs::path p("data/soft-link-to-soft-link-to-folder");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_regular_file, SoftLinkToFolderAbsolutePath) {
  fs::path p("data/soft-link-to-folder-absolute-path");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_regular_file, DeadSoftLink) {
  fs::path p("data/dead-soft-link");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_regular_file, HardLinkToFile) {
  fs::path p("data/hard-link-to-file");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, HardLinkToFileAbsolutePath) {
  fs::path p("data/hard-link-to-file-absolute-path");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, Negative) {
  fs::path p("DoesNotExist");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_regular_file, FileWithSpaceInTheName) {
  fs::path p("data/file with spaces in the name");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, FolderWithSpaceInTheName) {
  fs::path p("data/folder with spaces in the name");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_regular_file, FileUnderFolderWithNoReadPermissions) {
  fs::path p("data/folder-0311/file");
  ASSERT_TRUE(fs::is_regular_file(p));
}

TEST(is_regular_file, FolderUnderFolderWithNoReadPermissions) {
  fs::path p("data/folder-0311/folder");
  ASSERT_FALSE(fs::is_regular_file(p));
}

TEST(is_directory, RegularFile) {
  fs::path p("data/regular-file");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, RegularFolder) {
  fs::path p("data/regular-folder");
  ASSERT_TRUE(fs::is_directory(p));
}

TEST(is_directory, SoftLinkToFile) {
  fs::path p("data/soft-link-to-file");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, SoftLinkToSoftLinkToFile) {
  fs::path p("data/soft-link-to-soft-link-to-file");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, SoftLinkToFileAbsolutePath) {
  fs::path p("data/soft-link-to-file-absolute-path");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, SoftLinkToFolder) {
  fs::path p("data/soft-link-to-folder");
  ASSERT_TRUE(fs::is_directory(p));
}

TEST(is_directory, SoftLinkToSoftLinkToFolder) {
  fs::path p("data/soft-link-to-soft-link-to-folder");
  ASSERT_TRUE(fs::is_directory(p));
}

TEST(is_directory, SoftLinkToFolderAbsolutePath) {
  fs::path p("data/soft-link-to-folder-absolute-path");
  ASSERT_TRUE(fs::is_directory(p));
}

TEST(is_directory, DeadSoftLink) {
  fs::path p("data/dead-soft-link");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, HardLinkToFile) {
  fs::path p("data/hard-link-to-file");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, HardLinkToFileAbsolutePath) {
  fs::path p("data/hard-link-to-file-absolute-path");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, Negative) {
  fs::path p("DoesNotExist");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, FileWithSpaceInTheName) {
  fs::path p("data/file with spaces in the name");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, FolderWithSpaceInTheName) {
  fs::path p("data/folder with spaces in the name");
  ASSERT_TRUE(fs::is_directory(p));
}

TEST(is_directory, FileUnderFolderWithNoReadPermissions) {
  fs::path p("data/folder-0311/file");
  ASSERT_FALSE(fs::is_directory(p));
}

TEST(is_directory, FolderUnderFolderWithNoReadPermissions) {
  fs::path p("data/folder-0311/folder");
  ASSERT_TRUE(fs::is_directory(p));
}

TEST(path, ConstuctFromString) {
  std::string s = "ceraunoGraPh";
  fs::path p(s);
  ASSERT_EQ(p.string(), "ceraunoGraPh");
}

TEST(path, ConstuctFromConstString) {
  const std::string s = "stibIAlisM";
  fs::path p(s);
  ASSERT_EQ(p.string(), "stibIAlisM");
}

TEST(path, ParentPath) {
  fs::path p("MuTIViTY/georGeTTe");
  ASSERT_EQ(p.parent_path().string(), "MuTIViTY");
}

TEST(path, ParentPathAbsolute) {
  fs::path p("/AnoMphAlous/trAnecT");
  ASSERT_EQ(p.parent_path().string(), "/AnoMphAlous");
}

TEST(path, ParentPathExotic) {
  fs::path p("../../wiNdGAll/chArtreUse/../stEpNey/trAnecT");
  ASSERT_EQ(p.parent_path().string(), "../../wiNdGAll/chArtreUse/../stEpNey");
}

TEST(path, ParentPathMessed) {
  fs::path p("VetItiVe/..//..////..wOrmIl/zugtrompete///SedeRuNT");
  ASSERT_EQ(p.parent_path().string(),
            "VetItiVe/..//..////..wOrmIl/zugtrompete");
}

TEST(path, ParentPathRoot) {
  fs::path p("/");
  ASSERT_TRUE(p.parent_path().string().empty());
}

TEST(path, Extension) {
  fs::path p("enigMaTic.docx");
  ASSERT_EQ(p.extension().string(), ".docx");
}

TEST(path, ExtensionEmpty) {
  fs::path p("QuIxotIcE");
  ASSERT_TRUE(p.extension().string().empty());
}

TEST(path, ExtensionDotsInPath) {
  fs::path p("nebulOus/epHemeRal/quixOtIc/ambROsia...pdf");
  ASSERT_EQ(p.extension().string(), ".pdf");
}

TEST(path, ExtensionEvenMoreDotsInPath) {
  fs::path p("/ExotiC/Bl,UmBer/tRanS..cenDenCe/inCAnD.escEnT/mY.stErIous/"
             "eLepHanT/PrOd.iGioUs/vErNaCUlaR/pHaNt.AsMaGoriCaL/FoXy/"
             "ObL...iViOn/AmBivAlEnt/dIReSer..eNiTy/EsOteRiC/sErE..NdIPitY/"
             "sUblImInAL/oBeLIscArIo/syNerGy/TrAilBlAzEr.tXt");
  ASSERT_EQ(p.extension().string(), ".tXt");
}

TEST(path, IsRelativePositive) {
  fs::path p("BaMaBoO/CrYsTaLlInE/PhAnTaSmAgOrIa");
  EXPECT_TRUE(p.is_relative());
}

TEST(path, IsRelativeNegative) {
  fs::path p("/TrAnScEnDeNcE/InFInItEsImAl/EcLeCtIc/ObSeRvEr");
  EXPECT_FALSE(p.is_relative());
}

TEST(path, FilenameSingle) {
  fs::path p("ExOpHtHaLmOsCoPiC");
  EXPECT_EQ(p.filename().string(), "ExOpHtHaLmOsCoPiC");
}

TEST(path, FilenameAbsolute) {
  fs::path p("/cHrOnOsYnCrEtIsM/aMpHiBiOuS/mYtHiCaL");
  EXPECT_EQ(p.filename().string(), "mYtHiCaL");
}

TEST(path, FilenameRelative) {
  fs::path p("cAcOpHoNiC/iRrEpArAbLe/aBsTrUsE/fAnTaSmAgOrIaL");
  EXPECT_EQ(p.filename().string(), "fAnTaSmAgOrIaL");
}

TEST(path, FilenameRelativeExotic) {
  fs::path p(
      "../EtHeReAl/../../oPtImIsTiC/hYpErBoLe/dEcOnStRuCtIoNiSm/ExTrAvAgAnT");
  EXPECT_EQ(p.filename().string(), "ExTrAvAgAnT");
}

TEST(path, FilenameRelativeMessed) {
  fs::path p("..///..//ApHoTiC////QuInTeSsEnCe/../OsCiLLaTiOn///InCoRpOrEaLiTy/"
             "././/aLoOf.exe");
  EXPECT_EQ(p.filename().string(), "aLoOf.exe");
}

TEST(path, AssignmentTrivia) {
  fs::path src("Serpentine/Quixotic/Juxtapose/Ephemeral/Labyrinthine/Esoteric");
  fs::path dst("scelestic");
  dst = src;
  EXPECT_EQ(dst.string(),
            "Serpentine/Quixotic/Juxtapose/Ephemeral/Labyrinthine/Esoteric");
}

TEST(path, AssignmentOutOfScope) {
  fs::path dst = fs::path("emptysis/sinecure.dal");
  {
    fs::path src(fs::path("aedile/glumiferous/nesiote.baculus"));
    dst = src;
  }
  EXPECT_EQ(dst.string(), "aedile/glumiferous/nesiote.baculus");
}

TEST(path, EqualityPositive) {
  ASSERT_TRUE(fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL") ==
              fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL"));
  ASSERT_TRUE(fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL") ==
              "/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL");
  ASSERT_TRUE("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL" ==
              fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL"));
  ASSERT_FALSE(fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL") !=
               fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL"));
  ASSERT_FALSE(fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL") !=
               "/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL");
  ASSERT_FALSE("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL" !=
               fs::path("/ExquIsiTe/PhAnTaSmAgOrIc/InStInCtUaL"));
}

TEST(path, EqualityNegative) {
  ASSERT_FALSE(fs::path("/PoLyPhOnIc/AnImAtRoNiC") ==
               fs::path("rHiThMpHiC/qUaLiAtIvE/tRaNsGrEsSiOn/HyPoThEtIcAldf"));
  ASSERT_FALSE(fs::path("/PoLyPhOnIc/AnImAtRoNiC") ==
               "rHiThMpHiC/qUaLiAtIvE/tRaNsGrEsSiOn/HyPoThEtIcAldf");
  ASSERT_FALSE("/PoLyPhOnIc/AnImAtRoNiC" ==
               fs::path("rHiThMpHiC/qUaLiAtIvE/tRaNsGrEsSiOn/HyPoThEtIcAldf"));
  ASSERT_TRUE(fs::path("/PoLyPhOnIc/AnImAtRoNiC") !=
              fs::path("rHiThMpHiC/qUaLiAtIvE/tRaNsGrEsSiOn/HyPoThEtIcAldf"));
  ASSERT_TRUE(fs::path("/PoLyPhOnIc/AnImAtRoNiC") !=
              "rHiThMpHiC/qUaLiAtIvE/tRaNsGrEsSiOn/HyPoThEtIcAldf");
  ASSERT_TRUE("/PoLyPhOnIc/AnImAtRoNiC" !=
              fs::path("rHiThMpHiC/qUaLiAtIvE/tRaNsGrEsSiOn/HyPoThEtIcAldf"));
}

TEST(path, EqualityTricky) {
  // It appears that boost::filesystem::path handles redundant path separators
  // just fine, so we are
  ASSERT_TRUE(fs::path("/SyNChRoNiZe///InComPrEhEnSiBlE////ThErMoDyNaMiC") ==
              fs::path("/SyNChRoNiZe/InComPrEhEnSiBlE/ThErMoDyNaMiC"));
  ASSERT_TRUE(fs::path("/SyNChRoNiZe///InComPrEhEnSiBlE////ThErMoDyNaMiC") ==
              "/SyNChRoNiZe/InComPrEhEnSiBlE/ThErMoDyNaMiC");
  ASSERT_TRUE("/SyNChRoNiZe///InComPrEhEnSiBlE////ThErMoDyNaMiC" ==
              fs::path("/SyNChRoNiZe/InComPrEhEnSiBlE/ThErMoDyNaMiC"));
  ASSERT_FALSE(fs::path("/SyNChRoNiZe///InComPrEhEnSiBlE////ThErMoDyNaMiC") !=
               fs::path("/SyNChRoNiZe/InComPrEhEnSiBlE/ThErMoDyNaMiC"));
  ASSERT_FALSE(fs::path("/SyNChRoNiZe///InComPrEhEnSiBlE////ThErMoDyNaMiC") !=
               "/SyNChRoNiZe/InComPrEhEnSiBlE/ThErMoDyNaMiC");
  ASSERT_FALSE("/SyNChRoNiZe///InComPrEhEnSiBlE////ThErMoDyNaMiC" !=
               fs::path("/SyNChRoNiZe/InComPrEhEnSiBlE/ThErMoDyNaMiC"));
}

TEST(path, EqualityAnotherTricky) {
  // It appears that boost::filesystem::path doesn't canonicalize paths
  ASSERT_FALSE(fs::path("bless/../bali") == fs::path("bali"));
  ASSERT_TRUE(fs::path("bless/../bali") != fs::path("bali"));
}

TEST(directory_entry, trivia) {
  fs::directory_entry entry(fs::path("/ZephYr/dAta/filE.txT"));
  ASSERT_EQ(entry.path().string(), "/ZephYr/dAta/filE.txT");
}

std::vector<std::string> expected = {
    //
    "data/dead-soft-link",
    "data/file with spaces in the name",
    "data/folder with spaces in the name",
    "data/folder-0311",
    "data/hard-link-to-file",
    "data/hard-link-to-file-absolute-path",
    "data/regular-file",
    "data/regular-folder",
    "data/soft-link-to-file",
    "data/soft-link-to-file-absolute-path",
    "data/soft-link-to-folder",
    "data/soft-link-to-folder-absolute-path",
    "data/soft-link-to-soft-link-to-file",
    "data/soft-link-to-soft-link-to-folder",
};

TEST(directory_iterator, Loop) {
  std::vector<std::string> actual;
  fs::directory_iterator it(fs::path("data")), last;
  while (it != last) {
    actual.push_back(it->path().string());
    ++it;
  }
  ASSERT_THAT(actual, ::testing::UnorderedElementsAreArray(expected));
}

TEST(directory_iterator, RangeLoop) {
  std::vector<std::string> actual;
  for (const auto &entry : fs::directory_iterator(fs::path("data"))) {
    actual.push_back(entry.path().string());
  }
  ASSERT_THAT(actual, ::testing::UnorderedElementsAreArray(expected));
}

TEST(directory_iterator, ForEachClassic) {
  std::vector<std::string> actual;
  struct func {
    func(std::vector<std::string> &actual) : actual(actual) {}
    void operator()(const fs::directory_entry &entry) {
      actual.push_back(entry.path().string());
    }
    std::vector<std::string> &actual;
  };
  std::for_each(fs::directory_iterator(fs::path("data")),
                fs::directory_iterator(), func(actual));
  ASSERT_THAT(actual, ::testing::UnorderedElementsAreArray(expected));
}

TEST(directory_iterator, ForEachLambda) {
  std::vector<std::string> actual;
  std::for_each(fs::directory_iterator(fs::path("data")),
                fs::directory_iterator(),
                [&actual](fs::directory_entry &entry) {
                  actual.push_back(entry.path().string());
                });
  ASSERT_THAT(actual, ::testing::UnorderedElementsAreArray(expected));
}

TEST(directory_iterator, BackInserter) {
  std::vector<fs::directory_entry> entries;
  std::copy(fs::directory_iterator(fs::path("data")), fs::directory_iterator(),
            std::back_inserter(entries));
  std::vector<std::string> actual;
  actual.reserve(entries.size());
  std::transform(
      entries.begin(), entries.end(), std::back_inserter(actual),
      [](fs::directory_entry entry) { return entry.path().string(); });
  ASSERT_THAT(actual, ::testing::UnorderedElementsAreArray(expected));
}

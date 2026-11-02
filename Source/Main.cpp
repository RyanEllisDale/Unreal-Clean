// Includes :
#include <iostream>
#include <conio.h>
#include <filesystem>
#include "string"

void DeleteFolder(const std::filesystem::path& aRoot, const std::filesystem::path& aPath)
{
	const std::filesystem::path targetPath = aRoot / aPath;
	std::filesystem::remove_all(targetPath);
}

bool FindExtension(const std::filesystem::path& aRoot, const std::string& aExtension)
{
	for (const std::filesystem::directory_entry& currentFile : std::filesystem::directory_iterator(aRoot))
	{
		if ((currentFile.path().extension() == aExtension)) 
		{
			return true;
		}
	}

	return false;
}

void DeleteExtension(const std::filesystem::path& aRoot, const std::string& aExtension)
{
	for (const std::filesystem::directory_entry& currentFile : std::filesystem::directory_iterator(aRoot))
	{
		if ((currentFile.path().extension() == aExtension) || (currentFile.path().filename() == aExtension))
		{
			std::filesystem::remove(currentFile.path());
		}
	}
}

int main()
{
	// Requested Values :
	const std::filesystem::path root = std::filesystem::current_path();
	const std::filesystem::path folderTargets[] = { ".vs/","Binaries/","Intermediate/","Saved/" };
	const std::string extensionTargets[] = { ".sln",".slnx",".vsconfig" };

	// Early Exit : 
	if (FindExtension(root, ".uproject") == false)
	{
		std::cerr << "Not a Valid Unreal Project Folder" << std::endl;
		std::cerr << "Press Any Key to Exit" << std::endl;
		_getch();
		return -1;
	}

	// Folders :
	for (const std::filesystem::path& currentPath : folderTargets)
	{
		DeleteFolder(root, currentPath);
	}

	// Extensions :
	for (const std::string& currentExtension : extensionTargets)
	{
		DeleteExtension(root, currentExtension);
	}

	// Cleanup / End : 
	return 0;
}
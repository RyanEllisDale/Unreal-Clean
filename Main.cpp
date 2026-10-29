// Includes :
#include <iostream>
#include <filesystem>
#include "string"

void DeleteFolder(const std::filesystem::path& aRoot, const std::filesystem::path& aPath)
{
	const std::filesystem::path targetPath = aRoot / aPath;
	std::filesystem::remove_all(targetPath);
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
	const std::filesystem::path root = std::filesystem::current_path();
	const std::filesystem::path folderTargets[] = { ".vs/","Binaries/","Intermediate/","Saved/" };
	const std::string extensionTargets[] = { ".sln",".slnx",".vsconfig" };
 
	for (const std::filesystem::path& currentPath : folderTargets)
	{
		DeleteFolder(root, currentPath);
	}

	for (const std::string& currentExtension : extensionTargets)
	{
		DeleteExtension(root, currentExtension);
	}

	return 0;
}
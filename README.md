# Unreal Blutilities Examples.

These Examples are my notes based in this Udemy Course:

- https://www.udemy.com/course/becoming-an-unreal-automation-expert

## Setup your Project

You need to get Unreal Engine and Visual Studio with these dependencies:

![img](https://media.discordapp.net/attachments/749071688196685895/759122277157044324/unknown.png)

**NOTE:** Blutilities based in C++ only works if your UE4 project was created using a c++ project, if not you need to add c++ support to your project.

- You need to enable Editor Scripting Utilities Plugin in `Edit/Plugins/Scripting`.

You need to add some PublicDependencyModuleNames to your `YourProjectName.Build.cs` as "Blutility", "UMG", "EditorScriptingUtilities"  also you need add your Public include Paths

```cs
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Blutility", "UMG", "EditorScriptingUtilities" });

PublicIncludePaths.AddRange(new string[] {System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "Source/Editor/Blutility/Private" });
```

In this project you can find some examples about how you can use Blutilties to create tools to improve task that include Assets Actions, Actors in Scene Actions and world outliner, each commit content an example with their code in py cpp and bluepriting, you can get more detailed info in the course.

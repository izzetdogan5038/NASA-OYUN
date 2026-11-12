import re
p = r'''E:\UE_5.8\Engine\Source\Programs\UnrealBuildTool\Modes\ValidatePlatformsMode.cs'''
s = open(p, encoding='utf-8').read()
old = '''			foreach (UnrealTargetPlatform Platform in Platforms)
			{
				UEBuildPlatform.TryGetBuildPlatform(Platform, out UEBuildPlatform? BuildPlatform);
				string PlatformSDKString = "";
				if (bOutputSDKs)
				{
					PlatformSDKString = "<UNKNOWN>";
					if (BuildPlatform != null)
					{
						try
						{
							PlatformSDKString = UEBuildPlatform.GetSDK(Platform)!.GetMainVersion();
						}
						catch (Exception Ex)
						{
							ExceptionMessages.Add(Ex.Message.TrimEnd());
						}
					}
				}

				if (BuildPlatform != null && BuildPlatform.HasRequiredSDKsInstalled() == SDKStatus.Valid)
				{
					Logger.LogInformation("##PlatformValidate: {Platform} VALID {PlatformSdkString}", Platform.ToString(), PlatformSDKString);
				}
				else
				{
					Logger.LogInformation("##PlatformValidate: {Platform} INVALID {PlatformSdkString}", Platform.ToString(), PlatformSDKString);
				}
			}'''
new = '''			foreach (UnrealTargetPlatform Platform in Platforms)
			{
				UEBuildPlatform.TryGetBuildPlatform(Platform, out UEBuildPlatform? BuildPlatform);
				if (BuildPlatform == null) continue;
				if (BuildPlatform.HasRequiredSDKsInstalled() != SDKStatus.Valid) continue;

				string PlatformSDKString = "";
				if (bOutputSDKs)
				{
					PlatformSDKString = "<UNKNOWN>";
					try
					{
						PlatformSDKString = UEBuildPlatform.GetSDK(Platform)!.GetMainVersion();
					}
					catch (Exception Ex)
					{
						ExceptionMessages.Add(Ex.Message.TrimEnd());
						continue;
					}
				}

				Logger.LogInformation("##PlatformValidate: {Platform} VALID {PlatformSdkString}", Platform.ToString(), PlatformSDKString);
			}'''
assert old in s, 'old block not found'
s = s.replace(old, new)
open(p, 'w', encoding='utf-8').write(s)
print('patched OK')

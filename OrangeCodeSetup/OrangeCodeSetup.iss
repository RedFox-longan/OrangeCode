// Inno Setup Compiler 6.2.0
// 由 Inno 安装脚本向导生成的脚本。
// 有关创建 INNO 安装脚本文件的详细信息，请参阅文档！

// user
#define InstallTarget "user"  
// x86 x64 arm64 ia64 ia32 
#define Arch "arm64"
#define NameShort "OrangeCode"
#define IncompatibleArchAppId "64"
#define IncompatibleTargetAppId "32"


#define MyAppName "OrangeCode"
#define MyAppVersion "0.0.1-alpha"
#define MyAppPublisher "SpaceLongan"
#define MyAppURL "https://space-longan.beanflame.cn/"
#define MyAppExeName "OrangeCode.exe"
#define MyAppAssocName MyAppName + " File"
#define MyAppAssocExt ".txt"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt



[Setup]
AppId={{E7FAA0BE-0997-4056-B1EB-7FB39AB5EE21}
AppName={#MyAppName}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultGroupName={#MyAppName}
// Setup
AllowNoIcons=yes
OutputBaseFilename={#MyAppName}Setup-{#MyAppVersion}
Compression=lzma
SolidCompression=yes
ChangesEnvironment=yes
ChangesAssociations=yes
DisableProgramGroupPage=yes
AppVersion={#MyAppVersion}
ShowLanguageDialog=auto
WizardStyle=modern



#if "user" == InstallTarget
DefaultDirName={userpf}\{#MyAppName}
PrivilegesRequired=lowest
#else
DefaultDirName={autopf}\{#MyAppName}
#endif



//WizardImageFile="resources\inno-big-100.bmp,resources\inno-big-125.bmp,resources\inno-big-150.bmp,resources\inno-big-175.bmp,resources\inno-big-200.bmp,resources\inno-big-225.bmp,resources\inno-big-250.bmp"
//WizardSmallImageFile="resources\inno-small-100.bmp,resources\inno-small-125.bmp,resources\inno-small-150.bmp,resources\inno-small-175.bmp,resources\inno-small-200.bmp,resources\inno-small-225.bmp,resources\inno-small-250.bmp"
//SetupIconFile=resources\code.ico

// bplm
// UninstallDisplayIcon={app}\{#ExeBasename}.exe
// WizardImageFile=resources\bplmSetup-inno-small.bmp



UninstallDisplayIcon=OrangeCode.ico
SetupIconFile=OrangeCode.ico




[Languages]
Name: "english"; MessagesFile: "i18n\Default.en.isl,i18n\messages.en.isl"
Name: "simplifiedChinese"; MessagesFile: "i18n\Default.zh-cn.isl,i18n\messages.zh-cn.isl"


[UninstallDelete]
Type: filesandordirs; Name: "{app}\_"


[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; 
Name: "addtopath"; Description: "{cm:AddToPath}"; GroupDescription: "{cm:Other}"


[Files]
// 注意：不要在任何共享系统文件上使用 "Flags: ignoreversion"
Source: "OrangeCode\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs


[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent


[Registry]
#if "user" == InstallTarget
#define SoftwareClassesRootKey "HKCU"
#else
#define SoftwareClassesRootKey "HKLM"
#endif


Root: {#SoftwareClassesRootKey}; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: {#SoftwareClassesRootKey}; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: {#SoftwareClassesRootKey}; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: {#SoftwareClassesRootKey}; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: {#SoftwareClassesRootKey}; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".myp"; ValueData: ""





// Environment
#if "user" == InstallTarget
#define EnvironmentRootKey "HKCU"
#define EnvironmentKey "Environment"
#define Uninstall64RootKey "HKCU64"
#define Uninstall32RootKey "HKCU32"
#else
#define EnvironmentRootKey "HKLM"
#define EnvironmentKey "System\CurrentControlSet\Control\Session Manager\Environment"
#define Uninstall64RootKey "HKLM64"
#define Uninstall32RootKey "HKLM32"
#endif

Root: {#EnvironmentRootKey}; Subkey: "{#EnvironmentKey}"; ValueType: expandsz; ValueName: "Path"; ValueData: "{olddata};{app}\bin"; Tasks: addtopath; Check: NeedsAddPath(ExpandConstant('{app}\bin'))






[Code]
// 不允许安装冲突的体系结构
// 初始化设置安装器
function InitializeSetup(): Boolean;
var
  RegKey: String;
  ThisArch: String;
  AltArch: String;
begin
  Result := True;

  #if "user" == InstallTarget
    if not WizardSilent() and IsAdmin() then begin
      if MsgBox('This User Installer is not meant to be run as an Administrator. If you would like to install VS Code for all users in this system, download the System Installer instead from https://code.visualstudio.com. Are you sure you want to continue?', mbError, MB_OKCANCEL) = IDCANCEL then begin
        Result := False;
      end;
    end;
  #endif

  #if "user" == InstallTarget
    #if "ia32" == Arch || "arm64" == Arch
      #define IncompatibleArchRootKey "HKLM32"
    #else
      #define IncompatibleArchRootKey "HKLM64"
    #endif

    if Result and not WizardSilent() then begin
      RegKey := 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\' + copy('{#IncompatibleTargetAppId}', 2, 38) + '_is1';

      if RegKeyExists({#IncompatibleArchRootKey}, RegKey) then begin
        if MsgBox('{#NameShort} is already installed on this system for all users. We recommend first uninstalling that version before installing this one. Are you sure you want to continue the installation?', mbConfirmation, MB_YESNO) = IDNO then begin
          Result := False;
        end;
      end;
    end;
  #endif

  if Result and IsWin64 then begin
    RegKey := 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\' + copy('{#IncompatibleArchAppId}', 2, 38) + '_is1';

    if '{#Arch}' = 'ia32' then begin
      Result := not RegKeyExists({#Uninstall64RootKey}, RegKey);
      ThisArch := '32';
      AltArch := '64';
    end else begin
      Result := not RegKeyExists({#Uninstall32RootKey}, RegKey);
      ThisArch := '64';
      AltArch := '32';
    end;

    if not Result and not WizardSilent() then begin
      MsgBox('Please uninstall the ' + AltArch + '-bit version of {#NameShort} before installing this ' + ThisArch + '-bit version.', mbInformation, MB_OK);
    end;
  end;
end;

// -------------------------------------------

// 获得一些数组的字符串
// https://stackoverflow.com/a/23838239/261019
procedure Explode(var Dest: TArrayOfString; Text: String; Separator: String);
var
  i, p: Integer;
begin
  i := 0;
  repeat
    SetArrayLength(Dest, i+1);
    p := Pos(Separator,Text);
    if p > 0 then begin
      Dest[i] := Copy(Text, 1, p-1);
      Text := Copy(Text, p + Length(Separator), Length(Text));
      i := i + 1;
    end else begin
      Dest[i] := Text;
      Text := '';
    end;
  until Length(Text)=0;
end;


// 设置添加Path的bin
function NeedsAddPath(Param: string): boolean;
var
  OrigPath: string;
begin
  if not RegQueryStringValue({#EnvironmentRootKey}, '{#EnvironmentKey}', 'Path', OrigPath)
  then begin
    Result := True;
    exit;
  end;
  Result := Pos(';' + Param + ';', ';' + OrigPath + ';') = 0;
end;


// 设置删除Path的bin
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  Path: string;
  AppPath: string;
  Parts: TArrayOfString;
  NewPath: string;
  i: Integer;
begin
  if not CurUninstallStep = usUninstall then begin
    exit;
  end;
  if not RegQueryStringValue({#EnvironmentRootKey}, '{#EnvironmentKey}', 'Path', Path)
  then begin
    exit;
  end;
  NewPath := '';
  AppPath := ExpandConstant('{app}\bin')
  Explode(Parts, Path, ';');
  for i:=0 to GetArrayLength(Parts)-1 do begin
    if CompareText(Parts[i], AppPath) <> 0 then begin
      NewPath := NewPath + Parts[i];

      if i < GetArrayLength(Parts) - 1 then begin
        NewPath := NewPath + ';';
      end;
    end;
  end;
  RegWriteExpandStringValue({#EnvironmentRootKey}, '{#EnvironmentKey}', 'Path', NewPath);
end;







##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UOCVineyard
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232
ProjectPath            :=/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard
IntermediateDirectory  :=../build-$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=uoc
Date                   :=04/06/24
CodeLitePath           :=/home/uoc/.codelite
LinkerName             :=/usr/bin/g++-11
SharedObjectLinkerName :=/usr/bin/g++-11 -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=../lib
OutputFile             :=../lib/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="UOCVineyard.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++-11
CC       := /usr/bin/gcc-11
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_do.c$(ObjectSuffix) $(IntermediateDirectory)/src_weighing.c$(ObjectSuffix) $(IntermediateDirectory)/src_vineyardplot.c$(ObjectSuffix) $(IntermediateDirectory)/src_winegrower.c$(ObjectSuffix) $(IntermediateDirectory)/src_person.c$(ObjectSuffix) $(IntermediateDirectory)/src_date.c$(ObjectSuffix) $(IntermediateDirectory)/src_csv.c$(ObjectSuffix) $(IntermediateDirectory)/src_api.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList)
	@$(MakeDirCommand) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/.build-debug"
	@echo rebuilt > "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/.build-debug/UOCVineyard"

MakeIntermediateDirs:
	@test -d ../build-$(ConfigurationName) || $(MakeDirCommand) ../build-$(ConfigurationName)


../build-$(ConfigurationName):
	@test -d ../build-$(ConfigurationName) || $(MakeDirCommand) ../build-$(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_do.c$(ObjectSuffix): src/do.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_do.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_do.c$(DependSuffix) -MM src/do.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/do.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_do.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_do.c$(PreprocessSuffix): src/do.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_do.c$(PreprocessSuffix) src/do.c

$(IntermediateDirectory)/src_weighing.c$(ObjectSuffix): src/weighing.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_weighing.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_weighing.c$(DependSuffix) -MM src/weighing.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/weighing.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_weighing.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_weighing.c$(PreprocessSuffix): src/weighing.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_weighing.c$(PreprocessSuffix) src/weighing.c

$(IntermediateDirectory)/src_vineyardplot.c$(ObjectSuffix): src/vineyardplot.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vineyardplot.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vineyardplot.c$(DependSuffix) -MM src/vineyardplot.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/vineyardplot.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vineyardplot.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vineyardplot.c$(PreprocessSuffix): src/vineyardplot.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vineyardplot.c$(PreprocessSuffix) src/vineyardplot.c

$(IntermediateDirectory)/src_winegrower.c$(ObjectSuffix): src/winegrower.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_winegrower.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_winegrower.c$(DependSuffix) -MM src/winegrower.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/winegrower.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_winegrower.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_winegrower.c$(PreprocessSuffix): src/winegrower.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_winegrower.c$(PreprocessSuffix) src/winegrower.c

$(IntermediateDirectory)/src_person.c$(ObjectSuffix): src/person.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_person.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_person.c$(DependSuffix) -MM src/person.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/person.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_person.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_person.c$(PreprocessSuffix): src/person.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_person.c$(PreprocessSuffix) src/person.c

$(IntermediateDirectory)/src_date.c$(ObjectSuffix): src/date.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_date.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_date.c$(DependSuffix) -MM src/date.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/date.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_date.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_date.c$(PreprocessSuffix): src/date.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_date.c$(PreprocessSuffix) src/date.c

$(IntermediateDirectory)/src_csv.c$(ObjectSuffix): src/csv.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_csv.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_csv.c$(DependSuffix) -MM src/csv.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/csv.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_csv.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_csv.c$(PreprocessSuffix): src/csv.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_csv.c$(PreprocessSuffix) src/csv.c

$(IntermediateDirectory)/src_api.c$(ObjectSuffix): src/api.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_api.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_api.c$(DependSuffix) -MM src/api.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOC20232_PR3_Code/UOC20232/UOCVineyard/src/api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_api.c$(PreprocessSuffix): src/api.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_api.c$(PreprocessSuffix) src/api.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ../build-$(ConfigurationName)/



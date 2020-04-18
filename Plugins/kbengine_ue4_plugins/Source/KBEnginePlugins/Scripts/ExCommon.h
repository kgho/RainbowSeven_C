#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/GameEngine.h"
#include "ExCommon.generated.h"

//����Զ���Debug�����
#pragma region LogDebug
class KBENGINEPLUGINS_API DDRecord
{
private:
	//��������
	static TSharedPtr<DDRecord> RecordInst;
	//���ɵ��ַ���
	FString RecordInfo;
	//��ʾʱ��
	float ShowTime;
	//��ʾ��ɫ
	FColor ShowColor;
public:
	//��ӡģʽ, 0 : Debug, 1 : Log, 2 : Warning, 3 : Error
	uint8 PatternID;
public:
	//���캯��
	inline DDRecord() {}
	~DDRecord() {}
	static TSharedPtr<DDRecord> Get();
	//�趨����
	inline void InitParam(float InTime, FColor InColor)
	{
		ShowTime = InTime;
		ShowColor = InColor;
	}
	//ִ�д�ӡ����
	inline void Output() {
		switch (PatternID)
		{
		case 0:
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, ShowTime, ShowColor, RecordInfo);
		}
		break;
		case 1:
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *RecordInfo);
		}
		break;
		case 2:
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RecordInfo);
		}
		break;
		case 3:
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *RecordInfo);
		}
		break;
		}
		//����ַ���
		RecordInfo.Empty();
	}
	//��д������<<
	inline DDRecord& operator<<(FString Info) { RecordInfo.Append(Info); return *this; }
	inline DDRecord& operator<<(FName Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FText Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(const char* Info) { RecordInfo += Info; return *this; }
	inline DDRecord& operator<<(const char Info) { RecordInfo.AppendChar(Info); return *this; }
	inline DDRecord& operator<<(int32 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline DDRecord& operator<<(uint8 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline DDRecord& operator<<(uint64 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline DDRecord& operator<<(float Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline DDRecord& operator<<(double Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline DDRecord& operator<<(bool Info) { RecordInfo.Append(Info ? FString("true") : FString("false")); return *this; }
	inline DDRecord& operator<<(FVector2D Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FVector Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FRotator Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FQuat Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FTransform Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FMatrix Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FLinearColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline DDRecord& operator<<(FMargin Info) { RecordInfo.Append((FString::SanitizeFloat(Info.Left) + FString(" , ") + FString::SanitizeFloat(Info.Top) + FString(" , ") + FString::SanitizeFloat(Info.Right) + FString(" , ") + FString::SanitizeFloat(Info.Bottom))); return *this; }
	//���
	inline void operator<<(DDRecord& Record) { Record.Output(); }
};
//DDRecord::Get() << FString("sfdewhe") << FName << int << float << DDRecord::Get();
#pragma endregion
namespace DDH
{
	FORCEINLINE DDRecord& Debug(float InTime = 3000.f, FColor InColor = FColor::Yellow)
	{
		DDRecord::Get()->PatternID = 0;
		DDRecord::Get()->InitParam(InTime, InColor);
		return *DDRecord::Get();
	}
	FORCEINLINE DDRecord& Debug(FColor InColor)
	{
		return Debug(3000.f, InColor);
	}
	FORCEINLINE DDRecord& Log()
	{
		DDRecord::Get()->PatternID = 1;
		return *DDRecord::Get();
	}
	FORCEINLINE DDRecord& Warning()
	{
		DDRecord::Get()->PatternID = 2;
		return *DDRecord::Get();
	}
	FORCEINLINE DDRecord& Error()
	{
		DDRecord::Get()->PatternID = 3;
		return *DDRecord::Get();
	}
	FORCEINLINE DDRecord& Endl()
	{
		return *DDRecord::Get();
	}
	//�������Enumֵ��Ӧ��FString���, ֱ�����Value��Ӧ��ֵ
	template<typename TEnum>
	FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr)
			return FString("InValid");
		return EnumPtr->GetEnumName((int32)Value);
	}
	//�������Enumֵ��Ӧ��FName���
	template<typename TEnum>
	FORCEINLINE FName GetEnumValueAsName(const FString& Name, TEnum Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return FName("InValid");
		}
		return FName(*EnumPtr->GetEnumName((int32)Value));
	}
	//�������FName��Ӧ��Enum���
	template<typename TEnum>
	FORCEINLINE TEnum GetEnumValueFromName(const FString& Name, FName Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return TEnum(0);
		}
		return (TEnum)EnumPtr->GetIndexByName(Value);
	}
	//�������FName��Ӧ��Enum��������
	FORCEINLINE int32 GetEnumIndexFromName(const FString& Name, FName Value)
	{
		const UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *Name, true);
		if (!EnumPtr) {
			return -1;
		}
		return EnumPtr->GetIndexByName(Value);
	}
}
/**
 *
 */
UCLASS()
class KBENGINEPLUGINS_API UExCommon : public UObject
{
	GENERATED_BODY()
public:
	static UExCommon* Get();
protected:
	static UExCommon* ExInst;

};
object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1055#1086#1080#1089#1082' '#1092#1072#1081#1083#1086#1074
  ClientHeight = 209
  ClientWidth = 341
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object BytesPerSecLabel1: TLabel
    Left = 128
    Top = 50
    Width = 3
    Height = 13
  end
  object SecPerClustLabel2: TLabel
    Left = 128
    Top = 69
    Width = 3
    Height = 13
  end
  object BytesPerClustLabel3: TLabel
    Left = 128
    Top = 88
    Width = 3
    Height = 13
  end
  object InformationLabel4: TLabel
    Left = 181
    Top = 69
    Width = 3
    Height = 13
  end
  object NumSecLabel5: TLabel
    Left = 128
    Top = 107
    Width = 3
    Height = 13
  end
  object NumClustLabel6: TLabel
    Left = 128
    Top = 126
    Width = 3
    Height = 13
  end
  object Label7infoFor1: TLabel
    Left = 8
    Top = 50
    Width = 77
    Height = 13
    Caption = #1041#1072#1081#1090' '#1074' '#1089#1077#1082#1090#1086#1088#1077
  end
  object Label8infoFor2: TLabel
    Left = 8
    Top = 69
    Width = 108
    Height = 13
    Caption = #1057#1077#1082#1090#1086#1088#1086#1074' '#1074' '#1082#1083#1072#1089#1090#1077#1088#1077
  end
  object Label9infoFor3: TLabel
    Left = 8
    Top = 88
    Width = 83
    Height = 13
    Caption = #1041#1072#1081#1090' '#1074' '#1082#1083#1072#1089#1090#1077#1088#1077
  end
  object Label10infoFor5: TLabel
    Left = 8
    Top = 107
    Width = 80
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1089#1077#1082#1090#1086#1088#1086#1074
  end
  object Label11infoFor6: TLabel
    Left = 8
    Top = 126
    Width = 86
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1082#1083#1072#1089#1090#1077#1088#1086#1074
  end
  object LabelStartCluster: TLabel
    Left = 8
    Top = 147
    Width = 129
    Height = 13
    Caption = #1057#1082#1072#1085#1080#1088#1086#1074#1072#1090#1100' '#1089' '#1082#1083#1072#1089#1090#1077#1088#1072':'
  end
  object LabelEndCluster: TLabel
    Left = 8
    Top = 166
    Width = 130
    Height = 13
    Caption = #1057#1082#1072#1085#1080#1088#1086#1074#1072#1090#1100' '#1087#1086' '#1082#1083#1072#1089#1090#1077#1088':'
  end
  object PathEdit1: TEdit
    Left = 8
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '\\.\'#1057':'
  end
  object ScanButton1: TButton
    Left = 135
    Top = 6
    Width = 83
    Height = 25
    Caption = 'Start Scan'
    TabOrder = 1
    OnClick = ScanButton1Click
  end
  object StopButton2: TButton
    Left = 224
    Top = 6
    Width = 81
    Height = 25
    Caption = 'Stop Scan'
    TabOrder = 2
    OnClick = StopButton2Click
  end
  object StartClusterEdit1: TEdit
    Left = 143
    Top = 144
    Width = 75
    Height = 21
    TabOrder = 3
    Text = '1'
  end
  object EndClusterEdit2: TEdit
    Left = 143
    Top = 166
    Width = 75
    Height = 21
    TabOrder = 4
    Text = '2000'
  end
end

object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 432
  ClientWidth = 447
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
    Top = 34
    Width = 3
    Height = 13
  end
  object SecPerClustLabel2: TLabel
    Left = 128
    Top = 53
    Width = 3
    Height = 13
  end
  object BytesPerClustLabel3: TLabel
    Left = 128
    Top = 72
    Width = 3
    Height = 13
  end
  object InformationLabel4: TLabel
    Left = 181
    Top = 53
    Width = 3
    Height = 13
  end
  object NumSecLabel5: TLabel
    Left = 128
    Top = 91
    Width = 3
    Height = 13
  end
  object NumClustLabel6: TLabel
    Left = 128
    Top = 110
    Width = 3
    Height = 13
  end
  object Label7infoFor1: TLabel
    Left = 8
    Top = 34
    Width = 77
    Height = 13
    Caption = #1041#1072#1081#1090' '#1074' '#1089#1077#1082#1090#1086#1088#1077
  end
  object Label8infoFor2: TLabel
    Left = 8
    Top = 53
    Width = 108
    Height = 13
    Caption = #1057#1077#1082#1090#1086#1088#1086#1074' '#1074' '#1082#1083#1072#1089#1090#1077#1088#1077
  end
  object Label9infoFor3: TLabel
    Left = 8
    Top = 72
    Width = 83
    Height = 13
    Caption = #1041#1072#1081#1090' '#1074' '#1082#1083#1072#1089#1090#1077#1088#1077
  end
  object Label10infoFor5: TLabel
    Left = 8
    Top = 91
    Width = 80
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1089#1077#1082#1090#1086#1088#1086#1074
  end
  object Label11infoFor6: TLabel
    Left = 8
    Top = 110
    Width = 86
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1082#1083#1072#1089#1090#1077#1088#1086#1074
  end
  object Label12infoFor4: TLabel
    Left = 182
    Top = 34
    Width = 112
    Height = 13
    Caption = #1055#1086#1080#1089#1082' '#1092#1072#1081#1083#1086#1074' pdf, jpg'
  end
  object LabelStartCluster: TLabel
    Left = 8
    Top = 131
    Width = 129
    Height = 13
    Caption = #1057#1082#1072#1085#1080#1088#1086#1074#1072#1090#1100' '#1089' '#1082#1083#1072#1089#1090#1077#1088#1072':'
  end
  object LabelEndCluster: TLabel
    Left = 8
    Top = 150
    Width = 130
    Height = 13
    Caption = #1057#1082#1072#1085#1080#1088#1086#1074#1072#1090#1100' '#1087#1086' '#1082#1083#1072#1089#1090#1077#1088':'
  end
  object PathEdit1: TEdit
    Left = 8
    Top = -8
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '\\.\F:'
  end
  object ScanButton1: TButton
    Left = 135
    Top = -10
    Width = 83
    Height = 25
    Caption = 'Start Scan'
    TabOrder = 1
    OnClick = ScanButton1Click
  end
  object StopButton2: TButton
    Left = 224
    Top = -10
    Width = 81
    Height = 25
    Caption = 'Stop Scan'
    TabOrder = 2
    OnClick = StopButton2Click
  end
  object VirtualStringTree2: TVirtualStringTree
    Left = 8
    Top = 190
    Width = 305
    Height = 328
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 3
    Columns = <
      item
        Position = 0
        Text = 'ID'
        Width = 49
      end
      item
        Position = 1
        Text = 'Cluster Number'
        Width = 145
      end
      item
        Position = 2
        Text = 'Type'
        Width = 106
      end>
  end
  object StartClusterEdit1: TEdit
    Left = 143
    Top = 128
    Width = 75
    Height = 21
    TabOrder = 4
    Text = '1'
  end
  object EndClusterEdit2: TEdit
    Left = 143
    Top = 150
    Width = 75
    Height = 21
    TabOrder = 5
    Text = '2000'
  end
  object FullClustersCheckBox1: TCheckBox
    Left = 16
    Top = 168
    Width = 97
    Height = 17
    Caption = 'FullClustersCheckBox1'
    TabOrder = 6
  end
  object NTFSRadioButton1: TRadioButton
    Left = 304
    Top = 120
    Width = 113
    Height = 17
    Caption = 'NTFSRadioButton1'
    Color = clBtnFace
    Ctl3D = True
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 7
  end
  object FAT32RadioButton3: TRadioButton
    Left = 304
    Top = 143
    Width = 113
    Height = 17
    Caption = 'FAT32RadioButton3'
    TabOrder = 8
  end
  object exFatRadioButton2: TRadioButton
    Left = 304
    Top = 166
    Width = 113
    Height = 17
    Caption = 'exFatRadioButton2'
    TabOrder = 9
  end
end

modded class MissionServer {
    private const static string MISSION_FOLDER = "$profile:WaterWorld\\";
    private const static string WATERWORLD_SETTINGS = MISSION_FOLDER + "Settings.json";
    ref WaterData m_WaterData;

    void MissionServer() 
    {
      if (!m_WaterData)
      {
        InitWaterSettings();

        string worldName;
        string lake = "";
        GetGame().GetWorldName(worldName);
        worldName.ToLower();

        if (worldName == "enoch")
        {
          lake = "DZ\\water_bliss\\ponds\\enoch_50x50.p3d";
        }
        else
        {
          lake = "DZ\\water\\Ponds\\lake_50x50.p3d";
        }

        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(WaterSpawn, 2000, false, lake);
      }
    }
    void~MissionServer()
    {
      if (m_WaterData.Mode == 1)
      {
        m_WaterData.CurrentHeight += m_WaterData.Increment;

        if (m_WaterData.CurrentHeight > m_WaterData.MaxHeight)
        {
          m_WaterData.CurrentHeight = m_WaterData.MinHeight;
        }
      }
      JsonFileLoader < WaterData > .JsonSaveFile(WATERWORLD_SETTINGS, m_WaterData);
    }
    void WaterSpawn(string lake)
    {
      int total = 0;
      float height = m_WaterData.CurrentHeight;
      vector pos = Vector(0,height,0);
      for (pos[0] = 25; pos[0] <= GetGame().GetWorld().GetWorldSize(); pos[0] = pos[0] + 50)
      {
        for (pos[2] = 25; pos[2] <= GetGame().GetWorld().GetWorldSize(); pos[2] = pos[2] + 50)
        {
          GetGame().CreateStaticObjectUsingP3D(lake, pos, vector.Zero, 1);
          ++total;
        }
      }
      Print("Total Spawned Water objects: " + total);
    }
    void InitWaterSettings()
    {
        if (!FileExist(WATERWORLD_SETTINGS)) {
          if (!FileExist(MISSION_FOLDER)) MakeDirectory(MISSION_FOLDER);
          DefaultWaterSettings(m_WaterData);
          JsonFileLoader < WaterData > .JsonSaveFile(WATERWORLD_SETTINGS, m_WaterData);
        } else {
            m_WaterData = new WaterData();
          JsonFileLoader < WaterData > .JsonLoadFile(WATERWORLD_SETTINGS, m_WaterData);
        }
    }
    void DefaultWaterSettings(out WaterData Data) 
    {
        Data = new WaterData();
    }

}

class WaterData {
    int Version = 1;
    int CurrentHeight = 80;
    int Mode = 0;
    int MaxHeight = 100;
    int MinHeight = 70;
    float Increment = 1.0;
  }
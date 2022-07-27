{
    "version" : 2,
    "algorithms" : [
        {
            "id" : "xgb_global",
            "weight" : 1,
            "params" : {
              "campaigns_blacklist_file" : "xgb_global.blacklist",
              "feature_mapping_file" : "global.features"
              },
            "models" : [
                {
                    "method" : "xgboost",
                    "features_dimension" : 24,
                    "weight" : 1.0,
                    "features" : [ 
                        ["publisher"],
                        ["tag"],
                        ["sizeid"],
                        ["wd"],
                        ["hour"],
                        ["device"],
                        ["campaign"],
                        ["group"],
                        ["ccid"],
                        ["campaign_freq"],
                        ["campaign_freq_log"],
                        ["geoch"],
                        ["userch"],
                    ],
                    "file" : "global.xgb" 
                },
            ],
        },

log_info("akhenaten: localization config started")

game_languages = [
  { 
    lang:"en", caption:"English", key:"english",
    base_table:"localization_base_en", table:"localization_en", message_table:"eventmsg_en", game_messages:"game_messages_en"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"ru", caption:"Russian", key:"russian",
    base_table:"localization_base_ru", table:"localization_ru", message_table:"eventmsg_ru", game_messages:"game_messages_ru"
    symbols:"А,Б,В,Г,Д,Е,Ж,З,И,Й,К,Л,М,Н,О,П,Р,С,Т,У,Ф,Х,Ц,Ч,Ш,Щ,Ъ,Ы,Ь,Э,Ю,Я,а,б,в,г,д,е,ж,з,и,й,к,л,м,н,о,п,р,с,т,у,ф,х,ц,ч,ш,щ,ъ,ы,ь,э,ю,я"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:true, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"de", caption:"German", key:"german",
    base_table:"localization_base_de", table:"localization_de", message_table:"eventmsg_de", game_messages:"game_messages_de"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,Ä,ä,Ö,ö,Ü,ü,É,é,À,à,È,è,ù"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"fr", caption:"French", key:"french",   
    base_table:"localization_base_fr", table:"localization_fr", message_table:"eventmsg_fr", game_messages:"game_messages_fr"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"it", caption:"Italian", key:"italian",
    base_table:"localization_base_it", table:"localization_it", message_table:"eventmsg_it", game_messages:"game_messages_it"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"kr", caption:"Korean", key:"korean",
    base_table:"localization_base_kr", table:"localization_kr", message_table:"eventmsg_kr", game_messages:"game_messages_kr"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"po", caption:"Polish", key:"polish",
    base_table:"localization_base_po", table:"localization_po", message_table:"eventmsg_po", game_messages:"game_messages_po"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"pr", caption:"Portugese", key:"portugese",
    base_table:"localization_base_pr", table:"localization_pr", message_table:"eventmsg_pr", game_messages:"game_messages_pr"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"sp", caption:"Spanish", key:"spanish",
    base_table:"localization_base_sp", table:"localization_sp", message_table:"eventmsg_sp", game_messages:"game_messages_sp"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"  
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"ci", caption:"Chinese (Simple)", key:"chinese_s",
    base_table:"localization_base_ci", table:"localization_ci", message_table:"eventmsg_ci", game_messages:"game_messages_ci"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"  
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
  { 
    lang:"ch", caption:"Chinese (Tradition)", key:"chinese_c",
    base_table:"localization_base_ch", table:"localization_ch", message_table:"eventmsg_ch", game_messages:"game_messages_ch"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"  
    font_configs [
      { type: FONT_SMALL_PLAIN, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_LIGHT, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_NORMAL_WHITE_ON_DARK, size:14, color:0xffffffff, bold:true, line_height:14 },
      { type: FONT_NORMAL_YELLOW, size:14, color:0xffffff18, bold:true, line_height:14 },
      { type: FONT_NORMAL_BLUE, size:14, color:0xff0055ff, bold:true, line_height:14 },
      { type: FONT_LARGE_BLACK_ON_LIGHT, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_LARGE_BLACK_ON_DARK, size:18, color:0xff000000, bold:false, line_height:18 },
      { type: FONT_SMALL_OUTLINED, size:12, color:0xff000000, bold:false, line_height:12 },
      { type: FONT_NORMAL_BLACK_ON_DARK, size:14, color:0xff000000, bold:false, line_height:14 },
      { type: FONT_SMALL_SHADED, size:12, color:0xff000000, bold:true, line_height:12 }
    ]
  }
]
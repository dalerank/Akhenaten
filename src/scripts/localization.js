log_info("akhenaten: localization config started")

game_languages = [
  { 
    lang:"en", caption:"English", key:"english",
    base_table:"localization_base_en", table:"localization_en", message_table:"eventmsg_en"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"ru", caption:"Русский", key:"russian",
    base_table:"localization_base_ru", table:"localization_ru", message_table:"eventmsg_ru"
    symbols:"А,Б,В,Г,Д,Е,Ж,З,И,Й,К,Л,М,Н,О,П,Р,С,Т,У,Ф,Х,Ц,Ч,Ш,Щ,Ъ,Ы,Ь,Э,Ю,Я,а,б,в,г,д,е,ж,з,и,й,к,л,м,н,о,п,р,с,т,у,ф,х,ц,ч,ш,щ,ъ,ы,ь,э,ю,я"
    font:"data/neucha.ttf"
  }
  { 
    lang:"de", caption:"German", key:"german",
    base_table:"localization_base_de", table:"localization_de", message_table:"eventmsg_de"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,Ä,ä,Ö,ö,Ü,ü,É,é,À,à,È,è,ù"
    font:"data/neucha.ttf"
  }
  { 
    lang:"fr", caption:"French", key:"french",   
    base_table:"localization_base_fr", table:"localization_fr", message_table:"eventmsg_fr"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"it", caption:"Italian", key:"italian",
    base_table:"localization_base_it", table:"localization_it", message_table:"eventmsg_it"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"kr", caption:"Korean", key:"korean",
    base_table:"localization_base_kr", table:"localization_kr", message_table:"eventmsg_kr"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"po", caption:"Polish", key:"polish",
    base_table:"localization_base_po", table:"localization_po", message_table:"eventmsg_po"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"pr", caption:"Portugese", key:"portugese",
    base_table:"localization_base_pr", table:"localization_pr", message_table:"eventmsg_pr"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"sp", caption:"Spanish", key:"spanish",
    base_table:"localization_base_sp", table:"localization_sp", message_table:"eventmsg_sp"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"ci", caption:"Chinese (Simple)", key:"chinese_s",
    base_table:"localization_base_ci", table:"localization_ci", message_table:"eventmsg_ci"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
  { 
    lang:"ch", caption:"Chinese (Tradition)", key:"chinese_c",
    base_table:"localization_base_ch", table:"localization_ch", message_table:"eventmsg_ch"
    symbols:"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z"
    font:"data/neucha.ttf"
  }
]
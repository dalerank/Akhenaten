log_info("akhenaten: localization_en config started")

localization_en = [
     { key:"#TR_NO_PATCH_TITLE", text:""},
     { key:"#TR_NO_PATCH_MESSAGE", text:""},
     { key:"#TR_NO_EDITOR_TITLE", text:"편집기가 설치되지 않음"},
     { key:"#TR_NO_EDITOR_MESSAGE", text:"" },
     { key:"#TR_INVALID_LANGUAGE_TITLE", text:"잘못된 언어 디렉터리"},
     { key:"#TR_INVALID_LANGUAGE_MESSAGE", text:"현재 선택된 디렉터리는 사용 가능한 언어 팩을 포함하고 있지 않습니다. 기록에서 오류를 확인해 주세요."},
     { key:"#TR_BUTTON_OK", text:"확인"},
     { key:"#TR_BUTTON_CANCEL", text:"취소"},
     { key:"#TR_BUTTON_RESET_DEFAULTS", text:"기본값으로 초기화"},
     { key:"#TR_BUTTON_CONFIGURE_HOTKEYS", text:"단축키 설정"},
     { key:"#TR_CONFIG_TITLE", text:"설정 옵션"},
     { key:"#TR_CONFIG_LANGUAGE_LABEL", text:"언어:"},
     { key:"#TR_CONFIG_LANGUAGE_DEFAULT", text:"(기본)"},
     { key:"#TR_CONFIG_HEADER_UI_CHANGES", text:"사용자 인터페이스 변경"},
     { key:"#TR_CONFIG_HEADER_GAMEPLAY_CHANGES", text:"게임플레이 변경"},
     { key:"#TR_CONFIG_HEADER_GODS_CHANGES", text:"Gods changes"},
     { key:"#TR_CONFIG_HEADER_BUILDING_CHANGES", text:"Building changes"},
     { key:"#TR_CONFIG_HEADER_RESOURCE_CHANGES", text:"Resource changes"},
     { key:"#TR_CONFIG_SHOW_INTRO_VIDEO", text:"시작 영상 재생"},
     { key:"#TR_CONFIG_SIDEBAR_INFO", text:"게임 제어판에 추가 정보 표시"},
     { key:"#TR_CONFIG_SMOOTH_SCROLLING", text:"부드러운 화면이동 가능"},
     { key:"#TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE", text:"지형 평탄화 시 시각적 표현 향상"},
     { key:"#TR_CONFIG_ALLOW_CYCLING_TEMPLES", text:"각각의 신전을 연속으로 설치 가능"},
     { key:"#TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE", text:"저수조, 분수와 우물 설치 시 범위 표시"},
     { key:"#TR_CONFIG_SHOW_CONSTRUCTION_SIZE", text:"드래그 건설 시 전체 크기 표시"},
     { key:"#TR_CONFIG_HIGHLIGHT_LEGIONS", text:"커서가 올라간 군단 강조"},
     { key:"#TR_CONFIG_FIX_IMMIGRATION_BUG", text:"매우 어려움 난이도 이주 문제 수정"},
     { key:"#TR_CONFIG_FIX_100_YEAR_GHOSTS", text:"100세 이상 고령 주민 문제 수정"},
     { key:"#TR_CONFIG_FIX_EDITOR_EVENTS", text:"맞춤형 임무에서 황제 교체와 생존 시간 문제 수정"},
     { key:"#TR_HOTKEY_TITLE", text:"단축키 설정"},
     { key:"#TR_HOTKEY_LABEL", text:"단축키"},
     { key:"#TR_HOTKEY_ALTERNATIVE_LABEL", text:"대체"},
     { key:"#TR_HOTKEY_HEADER_ARROWS", text:"화살표키"},
     { key:"#TR_HOTKEY_HEADER_GLOBAL", text:"전역 단축키"},
     { key:"#TR_HOTKEY_HEADER_CITY", text:"도시 단축키"},
     { key:"#TR_HOTKEY_HEADER_ADVISORS", text:"자문관"},
     { key:"#TR_HOTKEY_HEADER_OVERLAYS", text:"맵보기"},
     { key:"#TR_HOTKEY_HEADER_BOOKMARKS", text:"도시 맵 즉시 이동"},
     { key:"#TR_HOTKEY_HEADER_EDITOR", text:"편집기"},
     { key:"#TR_HOTKEY_ARROW_UP", text:"위"},
     { key:"#TR_HOTKEY_ARROW_DOWN", text:"아래"},
     { key:"#TR_HOTKEY_ARROW_LEFT", text:"왼쪽"},
     { key:"#TR_HOTKEY_ARROW_RIGHT", text:"오른쪽"},
     { key:"#TR_HOTKEY_TOGGLE_FULLSCREEN", text:"전체화면 전환"},
     { key:"#TR_HOTKEY_CENTER_WINDOW", text:"창을 화면 가운데로"},
     { key:"#TR_HOTKEY_RESIZE_TO_640", text:"창 크기 640x480으로 변경"},
     { key:"#TR_HOTKEY_RESIZE_TO_800", text:"창 크기 800x600으로 변경"},
     { key:"#TR_HOTKEY_RESIZE_TO_1024", text:"창 크기 1024x768로 변경"},
     { key:"#TR_HOTKEY_SAVE_SCREENSHOT", text:"스크린샷 저장"},
     { key:"#TR_HOTKEY_SAVE_CITY_SCREENSHOT", text:"도시 전체 스크린샷 저장"},
     { key:"#TR_HOTKEY_LOAD_FILE", text:"파일 불러오기"},
     { key:"#TR_HOTKEY_SAVE_FILE", text:"파일 저장하기"},
     { key:"#TR_HOTKEY_INCREASE_GAME_SPEED", text:"게임 속도 증가"},
     { key:"#TR_HOTKEY_DECREASE_GAME_SPEED", text:"게임 속도 감소"},
     { key:"#TR_HOTKEY_TOGGLE_PAUSE", text:"일시 정지 전환"},
     { key:"#TR_HOTKEY_CYCLE_LEGION", text:"군단 돌아가며 보기"},
     { key:"#TR_HOTKEY_ROTATE_MAP_LEFT", text:"시계 반대 방향으로 맵 회전"},
     { key:"#TR_HOTKEY_ROTATE_MAP_RIGHT", text:"시계 방향으로 맵 회전"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_LABOR", text:"노동 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_MILITARY", text:"군단 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_IMPERIAL", text:"황제 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_RATINGS", text:"등급 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_TRADE", text:"무역 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_POPULATION", text:"인구 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_HEALTH", text:"보건 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_EDUCATION", text:"교육 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT", text:"오락 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_RELIGION", text:"종교 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_FINANCIAL", text:"재정 자문관"},
     { key:"#TR_HOTKEY_SHOW_ADVISOR_CHIEF", text:"수석 자문관"},
     { key:"#TR_HOTKEY_TOGGLE_OVERLAY", text:"현재 맵보기 전환"},
     { key:"#TR_HOTKEY_SHOW_OVERLAY_WATER", text:"물공급 맵보기 전환"},
     { key:"#TR_HOTKEY_SHOW_OVERLAY_FIRE", text:"화재 맵보기 전환"},
     { key:"#TR_HOTKEY_SHOW_OVERLAY_DAMAGE", text:"손상 맵보기 전환"},
     { key:"#TR_HOTKEY_SHOW_OVERLAY_CRIME", text:"범죄 맵보기 전환"},
     { key:"#TR_HOTKEY_SHOW_OVERLAY_PROBLEMS", text:"문제 맵보기 전환"},
     { key:"#TR_HOTKEY_GO_TO_BOOKMARK_1", text:"1지점으로 이동"},
     { key:"#TR_HOTKEY_GO_TO_BOOKMARK_2", text:"2지점으로 이동"},
     { key:"#TR_HOTKEY_GO_TO_BOOKMARK_3", text:"3지점으로 이동"},
     { key:"#TR_HOTKEY_GO_TO_BOOKMARK_4", text:"4지점으로 이동"},
     { key:"#TR_HOTKEY_SET_BOOKMARK_1", text:"1지점 설정"},
     { key:"#TR_HOTKEY_SET_BOOKMARK_2", text:"2지점 설정"},
     { key:"#TR_HOTKEY_SET_BOOKMARK_3", text:"3지점 설정"},
     { key:"#TR_HOTKEY_SET_BOOKMARK_4", text:"4지점 설정"},
     { key:"#TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO", text:"전투 정보 전환"},
     { key:"#TR_HOTKEY_EDIT_TITLE", text:"새 단축키 입력"}
     { key:"#mansion_protected_by_police", text:"경찰이 보호함"}
     { key:"#mansion_not_protected_theft", text:"미보호 — 도둑이 저축을 훔칠 수 있음"}

     { key: "#overlay_menu_normal", text: "일반" }
     { key: "#overlay_menu_risks", text: "위험" }
     { key: "#overlay_menu_water", text: "물" }
     { key: "#overlay_menu_entertainment", text: "오락" }
     { key: "#overlay_menu_religion", text: "종교" }
     { key: "#overlay_menu_education", text: "교육" }
     { key: "#overlay_menu_health", text: "보건" }
     { key: "#overlay_menu_administration", text: "행정" }
     { key: "#overlay_menu_food", text: "식량" }
     { key: "#overlay_menu_other", text: "기타" }

     { key: "#overlay_fire", text: "화재" }
     { key: "#overlay_damage", text: "피해" }
     { key: "#overlay_crime", text: "범죄" }
     { key: "#overlay_entertainment", text: "오락" }
     { key: "#overlay_booth", text: "저글러" }
     { key: "#overlay_bandstand", text: "음악가" }
     { key: "#overlay_pavilion", text: "무용수" }
     { key: "#overlay_senet_house", text: "세넷 플레이어" }
     { key: "#overlay_education", text: "교육" }
     { key: "#overlay_scribal_school", text: "서기관 학교" }
     { key: "#overlay_library", text: "도서관" }
     { key: "#overlay_academy", text: "학원" }
     { key: "#overlay_apothecary", text: "약방" }
     { key: "#overlay_dentist", text: "치과" }
     { key: "#overlay_physician", text: "의사" }
     { key: "#overlay_mortuary", text: "장례식장" }
     { key: "#overlay_tax_income", text: "세수입" }
     { key: "#overlay_bazaar_access", text: "시장 접근" }
     { key: "#overlay_desirability", text: "매력도" }
     { key: "#overlay_fertility", text: "비옥도" }
     { key: "#overlay_magistrate", text: "치안관" }
     { key: "#overlay_food_stocks", text: "식량 비축" }
     { key: "#overlay_labor", text: "노동" }
     { key: "#overlay_labor_access", text: "노동 접근" }
     { key: "#overlay_native", text: "원주민" }
     { key: "#overlay_problems", text: "문제" }
     { key: "#overlay_routing", text: "경로" }
     { key: "#overlay_malaria_risk", text: "말라리아 위험" }
     { key: "#overlay_health", text: "건강" }
     { key: "#overlay_criminal", text: "범죄자" }
     { key: "#overlay_osiris", text: "오시리스" }
     { key: "#overlay_ra", text: "라" }
     { key: "#overlay_ptah", text: "프타" }
     { key: "#overlay_seth", text: "세트" }
     { key: "#overlay_bast", text: "바스테트" }
     { key: "#TR_PALACE_TOOLTIP_UNEMPLOYMENT", text: "실업률" }
     { key: "#TR_PALACE_TOOLTIP_CULTURE_RATING", text: "문화 평점" }
     { key: "#TR_PALACE_TOOLTIP_PROSPERITY_RATING", text: "번영 평점" }
     { key: "#TR_PALACE_TOOLTIP_MONUMENT_RATING", text: "기념비 평점" }
     { key: "#TR_PALACE_TOOLTIP_KINGDOM_RATING", text: "왕국 평점" }
]
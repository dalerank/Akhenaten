log_info("akhenaten: ui advisor education started")

function education_advice_index() {
    var demandsEdu = city.houses.education
    var reqSchool = city.houses.requiring.school
    var reqLib = city.houses.requiring.library
    if (demandsEdu === 1) {
        return reqSchool ? 1 : 0
    }
    if (demandsEdu === 2) {
        return reqLib ? 3 : 2
    }
    if (demandsEdu === 3) {
        return 4
    }
    var coverage_school = city.coverage.school
    var coverage_academy = city.coverage.academy
    var coverage_library = city.coverage.library
    var advice_id
    if (!reqSchool) {
        advice_id = 5
    } else if (!reqLib) {
        if (coverage_school >= 100 && coverage_academy >= 100) {
            advice_id = 6
        } else if (coverage_school <= coverage_academy) {
            advice_id = 7
        } else {
            advice_id = 8
        }
    } else {
        if (coverage_school >= 100 && coverage_academy >= 100 && coverage_library >= 100) {
            advice_id = 6
        } else if (coverage_school <= coverage_academy && coverage_school <= coverage_library) {
            advice_id = 7
        } else if (coverage_academy <= coverage_school && coverage_academy <= coverage_library) {
            advice_id = 8
        } else if (coverage_library <= coverage_school && coverage_library <= coverage_academy) {
            advice_id = 9
        } else {
            advice_id = 6
        }
    }
    return advice_id
}

[es=advisor_window]
advisor_education_window {
    advisor: ADVISOR_EDUCATION
    ui {
        background   : outer_panel({size:[40, 19]})
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:7, pos:[10, 10] })
        title        : header({pos:[60, 17], text:[57, 0]})

        population   : text_center({pos:[20, 50], size:[200, 20], text:"${city.population} ${57.6}", font: FONT_NORMAL_BLACK_ON_LIGHT})
        school_age   : text_center({pos:[220, 50], size:[200, 20], text: "${city.population_kids} ${57.4}", font: FONT_NORMAL_BLACK_ON_LIGHT})
        academy_age  : text_center({pos:[420, 50], size:[200, 20], text: "${city.population_youngs} ${57.6}", font: FONT_NORMAL_BLACK_ON_LIGHT})

        header1      : text({text:[57, 4], pos:[180, 86], font:FONT_SMALL_PLAIN})
        header2      : text({text:[57, 5], pos:[290, 86], font:FONT_SMALL_PLAIN})
        header3      : text({text:[57, 6], pos:[478, 86], font:FONT_SMALL_PLAIN})

        inner_panel  : inner_panel({
            pos:[32, 108]
            size:[36, 8]
            default_font: FONT_NORMAL_WHITE_ON_DARK
            ui : {
                school_total     : text({pos:[5, 15], size:[100, 20]})
                school_active    : text_center({pos:[100, 15], size:[150, 20]})
                school_care      : text_center({pos:[280, 15], size:[40, 20]})
                school_covg      : text_center({pos:[440, 15], size:[60, 20]})

                academies_total  : text({pos:[5, 40], size:[100, 20]})
                academies_active : text_center({pos:[100, 40], size:[150, 20]})
                academies_care   : text_center({pos:[280, 40], size:[40, 20]})
                academies_covg   : text_center({pos:[440, 40], size:[60, 20]})

                libraries_total  : text({pos:[5, 65], size:[100, 20]})
                libraries_active : text_center({pos:[100, 65], size:[150, 20]})
                libraries_care   : text_center({pos:[280, 65], size:[40, 20]})
                libraries_covg   : text_center({pos:[440, 65], size:[60, 20]})
            }
        })

        education_advice : multiline({pos:[30, 250], size:[px(37), 0], font: FONT_NORMAL_BLACK_ON_LIGHT })
    }
}

[es=(advisor_education_window, init)]
function advisor_education_window_init(window) {
    var schoolAct = city.count_active_buildings(BUILDING_SCRIBAL_SCHOOL)
    var academyAct = city.count_active_buildings(BUILDING_ACADEMY)
    var libraryAct = city.count_active_buildings(BUILDING_LIBRARY)

    window.school_total.text = city.count_total_buildings(BUILDING_SCRIBAL_SCHOOL) + " " + __loc(8, 18)
    window.school_active.text = String(schoolAct)
    window.school_care.text = (75 * schoolAct) + " " + __loc(57, 7)
    window.school_covg.text = (75 * schoolAct) + " " + __loc(57, 7)

    window.academies_total.text = city.count_total_buildings(BUILDING_ACADEMY) + " " + __loc(8, 20)
    window.academies_active.text = String(academyAct)
    window.academies_care.text = (75 * academyAct) + " " + __loc(57, 8)
    window.academies_covg.text = (100 * academyAct) + " " + __loc(57, 7)

    window.libraries_total.text = city.count_total_buildings(BUILDING_LIBRARY) + " " + __loc(8, 22)
    window.libraries_active.text = String(libraryAct)
    window.libraries_care.text = (75 * libraryAct) + " " + __loc(57, 9)
    window.libraries_covg.text = (100 * libraryAct) + " " + __loc(57, 7)

    window.education_advice.text = __loc(57, 22 + education_advice_index())
}

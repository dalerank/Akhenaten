// Abu Simbel config tables (abu_simbel.js) hold together: 12 OG part kinds in order with art for 4 views,
// 16 parts of known kinds, 56 consecutive stages, each scaffold raised and lowered once, every carved part known.

function t395_check() {
    var cfg = building_abu_simbel
    var kinds = cfg.part_kinds
    var parts = cfg.parts
    var stages = cfg.stages
    var anims = cfg.animations
    if (!kinds || kinds.length != 12) {
        return '12 part kinds expected, got ' + (kinds ? kinds.length : 'none')
    }
    var kind_by_name = {}
    for (var k = 0; k < kinds.length; k++) {
        var row = kinds[k]
        if (row.kind != k) {
            return 'part_kinds row ' + k + ' says kind ' + row.kind
        }
        if (!row.name || kind_by_name[row.name] !== undefined) {
            return 'kind ' + k + ' has no name or a repeated one'
        }
        kind_by_name[row.name] = k
        if (row.size != 3 && row.size != 6) {
            return 'kind ' + row.name + ' size ' + row.size
        }
        if (row.on_rock !== true && row.on_rock !== false) {
            return 'kind ' + row.name + ' must say on_rock'
        }
        var has_family = !!row.family
        var views = row.views || []
        if (has_family == (views.length > 0)) {
            return 'kind ' + row.name + ' needs either a family or views'
        }
        for (var v = 0; v < 4; v++) {
            var image = has_family ? row.family + '_' + ((v + (row.rotate | 0)) % 4) : (views[v] && views[v].image)
            if (!image || !anims[image]) {
                return 'kind ' + row.name + ' view ' + v + ' has no art (' + image + ')'
            }
        }
        if (!has_family && views.length != 4) {
            return 'kind ' + row.name + ' has ' + views.length + ' views'
        }
    }

    if (!parts || parts.length != 16) {
        return '16 parts expected, got ' + (parts ? parts.length : 'none')
    }
    var part_ids = {}
    for (var p = 0; p < parts.length; p++) {
        if (kind_by_name[parts[p].kind] === undefined) {
            return 'part ' + parts[p].id + ' has unknown kind ' + parts[p].kind
        }
        if (!parts[p].id || part_ids[parts[p].id] !== undefined) {
            return 'part ' + p + ' has no id or a repeated one'
        }
        part_ids[parts[p].id] = p
    }

    if (!stages || stages.length != 56) {
        return '56 stages expected, got ' + (stages ? stages.length : 'none')
    }
    var scaffolds = cfg.scaffolds
    if (!scaffolds || scaffolds.length != 12) {
        return '12 scaffolds expected, got ' + (scaffolds ? scaffolds.length : 'none')
    }
    var scaffold_seen = {}
    for (var k = 0; k < scaffolds.length; k++) {
        var sc = scaffolds[k]
        if (sc.scaffold != k + 1 || !sc.name || scaffold_seen[sc.name] !== undefined) {
            return 'scaffold row ' + k + ': index ' + sc.scaffold + ' name ' + sc.name
        }
        if (!anims[sc.image] || !sc.view0 || !sc.view3) {
            return 'scaffold ' + sc.name + ' has no image or offsets'
        }
        scaffold_seen[sc.name] = 0
    }
    for (var s = 0; s < stages.length; s++) {
        var st = stages[s]
        if (st.stage != s) {
            return 'stage row ' + s + ' says stage ' + st.stage
        }
        if (!!st.scaffold == !!st.art) {
            return 'stage ' + s + ' needs either a scaffold or an art part'
        }
        if (st.scaffold) {
            if (scaffold_seen[st.scaffold] === undefined) {
                return 'stage ' + s + ' names unknown scaffold ' + st.scaffold
            }
            scaffold_seen[st.scaffold]++
        } else if (part_ids[st.art] === undefined) {
            return 'stage ' + s + ' carves unknown part ' + st.art
        }
        if (!(st.work > 0)) {
            return 'stage ' + s + ' has no work'
        }
    }
    for (var name in scaffold_seen) {
        if (scaffold_seen[name] != 2) {
            return 'scaffold ' + name + ' comes up ' + scaffold_seen[name] + ' times, expected 2'
        }
    }
    return ''
}

function run_test() {
    __log_info_native('[test:395] abu simbel config tables')
    var err = t395_check()
    if (err) {
        __log_info_native('[test:395] FAIL: ' + err)
    } else {
        __log_marker('t395_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] t395_ok')
}

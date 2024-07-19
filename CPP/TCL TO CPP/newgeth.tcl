proc reg_write {addr val} {
    mwr [expr {$addr + 0x40000000}] $val
}

proc reg_read {addr} {

    set retval [mrd [expr {$addr + 0x40000000}]] 
    variable reg_val
    scan [lindex [split $retval ":"] 1] "%x" reg_val 
    return $reg_val
} 

proc get_prbs {} {

    set prbs_val [reg_read 0x08]
    return $prbs_val
}

proc get_prbs_string {} { 
    set prbs_val [get_prbs]
    variable prbs_string

    switch $prbs_val {
        0 {
            set prbs_string "None"
        }
        1 {
            set prbs_string "PRBS-7"
        }
        2 {
            set prbs_string "PRBS-9"
        }
        3 {
            set prbs_string "PRBS-15"
        }
        5 {
            set prbs_string "PRBS-23"
        }
        default {
            set prbs_string "unknown"
        }
    }
    return $prbs_string
}

proc get_ber {err_cnt smp_cnt} {

    if { 0 == $err_cnt } {
        set ber [expr { 1.0 / $smp_cnt} ]
    } else {
        if { 0 == $smp_cnt } { scan "1" "%e" ber } else {
            set ber [expr {[expr {$err_cnt * 1}] / [expr {$smp_cnt + $err_cnt}] + 0.0}]
        }
    }
    scan $ber "%e" ber
    return $ber
}


proc print_result {measure_arr} {

    set cos 1
    foreach i $measure_arr {
        if {$cos} {
            puts -nonewline "[lindex $i 0], [format "%i" [lindex $i 1]], [lindex $i 2], "
            puts -nonewline $::g_fileId "[lindex $i 0], [format "%i" [lindex $i 1]], [lindex $i 2], "
            set cos 0
        } else {
            puts -nonewline "[format "%0.2e" [lindex $i 0]], [format "%0.2e" [lindex $i 1]], [format "%0.2e" [lindex $i 2]], [format "%0.1f" [lindex $i 3]], "
            puts -nonewline $::g_fileId "[format "%0.2e" [lindex $i 0]], [format "%0.2e" [lindex $i 1]], [format "%0.2e" [lindex $i 2]], [format "%0.1f" [lindex $i 3]], "
        }
    }
    puts ""
    puts $::g_fileId ""

}

proc get_Yoffset {base_V base_ber curr_ber} {
    set a [::tcl::mathfunc::log10 $base_ber]
    set b [::tcl::mathfunc::log10 $curr_ber]

    return [expr {$base_V * $b / $a}]
}

proc print_config_scan_param {YPAmpV YNAmpV Xoff_min Xoff_max Xoff_step Yoff_min Yoff_max Yoff_step ber_limit prbs test_type} {

    puts "+Yvolatge mv, $YPAmpV"
    puts "-Yvolatge mv, $YNAmpV"
    puts "XoffsMin, $Xoff_min"
    puts "XoffsMax, $Xoff_max" 
    if { 0 != $Yoff_step } {
        puts "YoffStep, $Yoff_step" 
        puts "YoffsMin, $Yoff_min" 
        puts "yoffsMax, $Yoff_max" 
        puts "YoffStep, $Yoff_step" 
    } else {
        puts "Yoff, $Yoff_min"
    }

    puts "BerLimit, $ber_limit"
    puts "PRBS, $prbs"
    puts "TestType, $test_type"

    puts $::g_fileId "+Yvolatge mv, $YPAmpV" 
    puts $::g_fileId "-Yvolatge mV, $YNAmpV" 
    puts $::g_fileId "xoffsMin, $Xoff_min" 
    puts $::g_fileId "XoffsMax, $Xoff_max" 
    puts $::g_fileId "xstep, $Xoff_step"
    if { 0 != $Yoff_step } {
        puts $::g_fileId "Yoffstep, $Yoff_step" 
        puts $::g_fileId "YoffsMin, $Yoff_min" 
        puts $::g_fileId "YoffsMax, $Yoff_max" 
        puts $::g_fileId "Yoffstep, $Yoff_step" 
    } else {
        puts $::g_fileId "Yoff, $Yoff_min"
    }
    puts $::g_fileId "Berlimit, $ber_limit" 
    puts $::g_fileId "PRBS, $prbs"
    puts $::g_fileId "TestType, $test_type"
}


proc getvolt {phase} {

    set Yoff [getYoffset]
    set Xoff [getXoffset]

    if { "POS" == $phase } { 
        setYoffset 0
    } elseif { "NEG" == $phase } {
        setYoffset -1
    }

    setXoffset 0

    set volt [_getVoltage]

    setYoffset $Yoff
    setXoffset $Xoff
      
    return $volt
}

proc getvoltage {} {

    variable err_cnt
    variable smp_cnt
    set presc 0
    set step 1
    set tmp_presc [reg_read 0x24]

    if { [getYoffset] < 0 } {
        set Hoffs -1
        set step [expr {$step * -1}]
    } else {
        set Hoffs 0
    }

    mwr 0x40000000 1
    while { 0 == [reg_read_0x04] } {}

    reg_write 0x08 1
    reg_write 0x18 1

    reg_write 0x24 $presc
    set vs_range 1.5

    while{ 1 } {
        setYoffset $Hoffs 
        do_single_scan
        scan [expr {[reg_read 0x30] * [expr { 1 + pow(2, [reg_read 0x24])}]}] "%e" err_cnt
        scan [expr {[reg_read 0x34] * [expr { 1 + pow(2, [reg_read 0x24])}]}] "%e" smp_cnt
        gth reset
        if { 0 == $err_cnt } {
            incr Hoffs $step
        } else {
            reg_write 0x24 $tmp_presc 
            break
        }
    }
    return [expr {$Hoffs * $vs_range}]
}

variable g_YAmpVP 0
variable g_YAmpVN 0
variable g_fileId
variable g_date [clock format [clock seconds] -format %d_%b_y_%H%M%S]
variable g_filename "TrenzOutScan_$::g_date.txt"
variable g_filepath "C:\\Users\\ST8782\\Documents\\vitis\\Test2\\app_component\\_ide\\psinit\\$::g_filename"
variable g_berLimit

proc do_single_scan {} {
    reg_write 0x28 1
    after 1
    reg_write 0x38 123
    while { 0 == [reg_read 0x2c] } {
        after 1
        reg_write 0x38 123
    }
}

proc setYoffset {Yoffset} {
    if { $Yoffset > 127 || $Yoffset < -127 } {
        puts "setYoffset out of range"
    }
    if { $Yoffset < 0 } {
        set $Yoffset [expr {[expr {$Yoffset * -1}] | 0x80}]
    }
    reg_write 0x1c $Yoffset
}

proc setXoffset {Xoffset} {
    set max_reg 0x7ff
    set offs $Xoffset
    if {$Xoffset < 0} {
        set offs [expr {$offs * -1}]
        incr offs -1
        set offs [expr {[expr {[expr {$max_reg - $offs}] & $max_reg}] | 0x800}]
    }
    reg_write 0x20 $offs
}

proc getXoffset {} {
    set max_reg 0x7ff
    set offs [reg_read 0x20]

    if {$offs & 0x800} {
        set offs [expr {$offs & $max_reg}]
        incr offs -1
        set offs [expr {[expr {$max_reg - $offs}] * -1}]
    }
    return $offs
}

proc getYoffset {} {
    set max_reg 0x7f
    set reg_val [reg_read 0x1c]
    if { [expr {$reg_val & [expr {1 << 7}] }] } { 
        set reg_val [expr {$reg_val * -1}]
    }
    return $reg_val
}

proc gth_reset() {
    mwr 0x40000000 1
    while { 0 == [reg_read 0x04] } {}
}

proc eye_scan {Xmin Xmax Xstep measure_pts} {

    set measure {}
    set Xoffset $Xmin
    variable err_cnt
    variable smp_cnt
    variable min_ber
    variable max_ber
    set ber_delta_limit 0.5
    set nmb_of_reapets_lim 5
    if {0} {internal variable}
    set nmb_of_reapets 0
    set repeated 0

    while { $Xoffset < $Xmax } {
        set measure_cnt 1
        set min_ber 1
        set max_ber 0
        while { $measure_cnt < $measure_pts} {
            if ( 0 == $measure_cnt ){
                set measure {}
                lappend measure [list $Xoffset [getYoffset] $measure_pts]
            }

            setXoffset $Xoffset
            do_single_scan
            scan [expr {[reg_read 0x30] * [expr {1 + pow(2, [reg_read 0x24])}]}] "%e" err_cnt
            scan [expr {[reg_read 0x34] * [expr {1 + pow(2, [reg_read 0x24])}]}] "%e" smp_cnt

            gth_reset
            set curr_ber [get_ber $err_cnt $smp_cnt]
            lappend measure [list $err_cnt $smp_cnt $curr_ber [get_Yoffset $::g_YAmpVP $::g_berLimit $curr_ber]] 
            if { $max_ber < $curr_ber } {
                set max_ber $curr_ber
            }
            if {$min_ber > $curr_ber} {
                set min_ber $curr_ber
            }
            incr measure_cnt 1
        }

        print_result $measure
        if { $nmb_of_reapets == 0 } {
            if {$max_ber != $min_ber} {
                set ber_delta [expr {abs([expr {[::tcl::mathfunc::log10 $min_ber] - [::tcl::mathfunc::log10 $max_ber]}])}]
            } else { set ber_delta 0 }
            if { ($ber_delta > $ber_delta_limit) && ($measure_pts > 1) && (0 == $repeated) } {
                set nmb_of_reapets [expr {round([expr {$ber_delta / $ber_delta_limit}])}]
                if { $nmb_of_reapets > $nmb_of_reapets_lim } {
                    set nmb_of_reapets $nmb_of_reapets_lim
                }
                puts "Repeats: $nmb_of_reapets Delta: $ber delta"
            } else {
                incr Xoffset $Xstep
                set repeated 0
            }
        } else {
            incr nmb_of_reapets -1
            set repeated 1
        }
    }
}

proc eye_matrix_scan {Xmin Xstep Xmax Ymin Ystep Ymax} {

    if { $Xmax < $Xmin} {
        puts "Xmax must be > Xmin" 
        return
    }
    if { $Ymax < $Ymin} {
        puts "Ymax must be > Ymin" 
        return
    }

    set::g_fileId [open $::g_filepath "w"]
    print_config_scan_param $::g_YAmpVP $::g_YAmpVN $Xmin $Xmax $Xstep $Ymin $Ymax $Ystep $::g_berlimit [get_prbs_string] "Matrixscan" 
    for { set y $Ymin } { $y <= $Ymax } {incr y $Ystep} {
        setYoffset $y
        eye_scan $Xmin $Xmax $Xstep 1
    }
    close $::g_fileId
}

if {0} {This one should be used instead of eye_scan - if you gonna use eye_scan
please remember about file to write output }
proc eye_horiz_scan {Xmin xstep Xmax MeasurePts Yoff} {

    if { $Xmax < $Xmin } {
        puts "xmax must be Xmin",
        return
    }

    if { 0 <= $Yoff } {
        setYoffset 1
    } else {
        reg_write 0x1c 0x80
    }
    
    if { 0 == $::g_YAmpVP } {
        set ::g_YAmpVP 180
    }
    if {0 == $::g_YAmpVN } {
        set ::g_YAmpVN -179
    }

    set ::g_fileId [open $::g_filepath "w"]

    print_config_scan_param $::g_YAmpVP $::g_YAmpVN $Xmin $Xmax $Xstep [getYoffset] [getYoffset] 0 $::g_berLimit [get_prbs_string] "OneHorizScan" 
    eye_scan $Xmin $Xmax $Xstep $MeasurePts

    close $::g_fileId

}

proc getPrescRegval {presc} {

    switch $presc {
        None {
            return 0
        }
        PRBS7 {
            return 1
        }
        PRBS15 {
            return 2
        }
        PRBS23 {
            return 3
        }
        PRBS31 {
            return 5
        }
    }
    return -1
}

proc reset_gth {} {
    mwr 0x40000000 1
    if { 1 == [reg_read 0x04] } {
        puts "GTH ready"
    } else {
        puts "GTH not ready" 
        return -1
    }
}

proc set_eye {prbs presc} {

    reset_gth
    set presc $presc

    set prbs_reg [getPrescRegval $prbs]

    if { 0 > $prbs_reg } {
        puts "Unknown PRBS: $prbs"
        puts "valid options: None, PRBS7, PRBS15, PRBS23, PRBS31" 
        return
    }

    reg_write 0x08 $prbs_reg
    reg_write 0x18 1
    reg_write 0x1c 0
    if {0} {Y axis}
    reg_write 0x20 0
    reg_write 0x24 $presc
}

proc init_eye_user {prbs presc} {
    set_eye $prbs $presc 
    print_config
}

proc init_eye_default {} {

    set_eye "PRBS7" 10 
    print_config
}

proc print_config {} {

    set ::g_YAmpVP [getVolt POS]
    set ::g_YAmpVN [getVolt NEG]

    if {0} {prescaler defines BER limit according to formula to calculate berLimit}
    set ::g_berLimit [format "%0.2e" [get_ber 0 [expr {65535 * [expr {1 + pow(2, [reg_read 0x24])}]}]]]

    puts "Yoffset is set to [getYoffset]"
    puts "Yoffset is set to [getXoffset]" 
    puts "Yoffset is set to [getXoffset]"
    puts "PRBS is set to [get_prbs_string]"
    puts "BER limit is $::g_berLimit"
    puts "voltage $::g_YAmpVP $::g_YAmpVN mv"
}

proc gth_self_test {} {

    puts "LINK TEST"

    set_eye PRBS7 1
    do_single_scan

    set err_cnt [expr {[reg_read 0x30] * [expr {1 + pow(2, [reg_read 0x24])}]}]
    set smp_cnt [expr {[reg_read 0x34] * [expr {1 + pow(2, [reg_read 0x24])}]}]
    
    if {0} { assumption is to have low ben here } 
    set curr_ber [get_ber $err_cnt $smp_cnt]

    if { 1e-2 > $curr_ber } {
        puts "LINK TEST: OK!"
    } else {
        puts "LINK TEST: BAD LINK"
    }
}

proc run {} {
    init_eye_default
    gth_self_test
    eye_horiz_scan -1 1 1 5
}


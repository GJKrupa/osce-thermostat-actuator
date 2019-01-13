radius = 23.5;
segments = 180;
rotate([180,0,0]) {
    union() {
        difference() {
            for (i = [0:2:359]) {
                rotate([0,0,i]) {
                    translate([0-radius,0,0]) {
                        rotate([0,15,0]) {
                            rotate(45,0,0) {
                                cube([1,1,7],true);
                            }
                        }
                    }
                }
            }
            translate([0,0,-4.2]) {
                cylinder(1, r=radius+2, true);
            }
        }
        difference() {
            translate([0,0,3.3]) { 
                cylinder(2, r=radius+0.5,true, $fn=segments);
            }
            
            translate([0,0,1.8]) { 
                cylinder(5, r=radius-2,true, $fn=segments);
            }
        }
        
        translate([0,0,4.3]) {
            difference() {
                cube([(radius*2)-0.5,10,2],true);
                for (i = [0:5:15]) {
                    translate([i,0,-2.5]) {
                        cylinder(5, r=1, true, $fn=36);
                    }
                    translate([0-i,0,-2.5]) {
                        cylinder(5, r=1, true, $fn=36);
                    }
                }
            }
        }
    } 
}



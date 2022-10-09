.pragma library

function rotatePoint(c, angle, p) {
    const degree = angle * (Math.PI/180);
    var sin = Math.sin(degree);
    var cos = Math.cos(degree);

    // translate point back to origin:
    p.x -= c.x;
    p.y -= c.y;

    // rotate point
    var xnew = p.x * cos - p.y * sin;
    var ynew = p.x * sin + p.y * cos;

    // translate point back:
    p.x = xnew + c.x;
    p.y = ynew + c.y;
    return p;
}

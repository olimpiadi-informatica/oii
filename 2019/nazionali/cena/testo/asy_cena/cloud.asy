path cloudpath(path p, real minArcRadius, real maxArcScale = 1.0)
{
    real overlap = 0.9;
    real pLength = arclength(p);

    // create cloud arc radii
    real[] radii;
    while(2*overlap * sum(radii) < pLength)
    {
        radii.push(minArcRadius * (1.0 + (unitrand() * (maxArcScale - 1.0))));
    }

    // scale radii to avoid large arc overlap at beginning and end of path p
    radii = radii * (pLength / (2*overlap * sum(radii)));

    // create overlapping arcs exterior to path p
    path arcs[];
    real currentTime = 0.0;
    for (int i = 0; i < radii.length; ++i)
    {
        pair circleCenter = (arcpoint(p, currentTime));
        path thisCircle = shift(circleCenter)*scale(radii[i])*unitcircle;
        pair[] intersects = intersectionpoints(thisCircle, p);
        path thisArc = arc(circleCenter, intersects[0], intersects[1], CW);
        if (inside(p, relpoint(thisArc, 0.1)))
        {
            thisArc = arc(circleCenter, intersects[0], intersects[1], CCW);
        }
        arcs.push(thisArc);
        if (i < radii.length - 1)
        {
            currentTime += overlap * (radii[i] + radii[i+1]);
        }
    }

    draw(p, red); // comment out to hide construction
    draw(arcs, mediumgray); // comment out to hide construction

    return buildcycle(... arcs);
}

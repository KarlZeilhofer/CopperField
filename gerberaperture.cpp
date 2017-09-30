#include "gerberaperture.h"
#include <QPainterPath>

#include <cmath>

QPainterPath GerberAperture::getPath() const
{
	QPainterPath p;

	switch(type)
	{
	case Circle:
		p.addEllipse(-sizeX/2, -sizeX/2, sizeX, sizeX);
		break;
	case Rect:
		p.addRect(-sizeX/2, -sizeY/2, sizeX, sizeY);
		break;
	case Oval:
		if(sizeX > sizeY){
			p.moveTo(+(sizeX-sizeY)/2, -sizeY/2);
			p.lineTo(-(sizeX-sizeY)/2, -sizeY/2);
			p.arcTo(-sizeX/2, -sizeY/2, sizeY, sizeY, 90, 180);
			p.lineTo(+(sizeX-sizeY)/2, +sizeY/2);
			p.arcTo(+(sizeX-sizeY)/2-sizeY/2, -sizeY/2, sizeY, sizeY, -90, 180);
			p.closeSubpath();
		}else if(sizeY > sizeX){
			p.moveTo(sizeX/2, +(sizeY-sizeX)/2);
			p.lineTo(sizeX/2, -(sizeY-sizeX)/2);
			p.arcTo(-sizeX/2, -sizeY/2, sizeX, sizeX, 0, 180);
			p.lineTo(-sizeX/2, +(sizeY-sizeX)/2);
			p.arcTo(-sizeX/2, +(sizeY-sizeX)/2-sizeX/2, sizeX, sizeX, 180, 180);
			p.closeSubpath();
		}else{ // sizeX = sizeY
			p.addEllipse(-sizeX/2, -sizeX/2, sizeX, sizeX);
		}
		break;
	}
	return p;
}


// make exposure-line with this aperture from (0/0) to (delta.x/delta.y)
QPainterPath GerberAperture::getLinePath(const QPointF& d) const
{
	QPainterPath p;

	switch(type)
	{
	case Circle:
		{
			qreal r = sizeX/2;
			qreal phi = atan2(d.y(),d.x()); // angle of line in radiants

//			if(phi<0){ // use only positive angles
//				phi += M_PI;
//			}
			p.moveTo(d.x()-r*sin(phi), d.y()+r*cos(phi));
			p.lineTo(-r*sin(phi), +r*cos(phi));
			p.arcTo(-r,-r, 2*r, 2*r, -(phi+M_PI/2)/(2*M_PI)*360, -180); // invert angles due to inconsistancy of acrTo
			p.lineTo(d.x()+r*sin(phi), d.y()-r*cos(phi));
			p.arcTo(d.x()-r,d.y()-r, 2*r, 2*r, -(phi-M_PI/2)/(2*M_PI)*360, -180); // invert angles due to inconsistancy of acrTo
			p.closeSubpath();

			// add center line:
//			p.moveTo(0,0);
//			p.lineTo(d);
		}break;
	case Rect:
		{
			qreal rh = sizeY/2;
			qreal rw = sizeX/2;

			if(d.y()==0) // horizontal line
			{
				if(d.x()>=0)
					p.addRect(-rw, -rh, d.x()+2*rw, 2*rh);
				else
					p.addRect(+rw, -rh, d.x()-2*rw, 2*rh);
			}else if(d.x()==0) // vertical line
			{
				if(d.y()>=0)
					p.addRect(-rw, -rh, 2*rw, d.y()+2*rh);
				else
					p.addRect(-rw, +rh, 2*rw, d.y()-2*rh);
			}else if(d.x()>0 && d.y()>0){ // 1. Quadrant
				p.moveTo(d.x()-rw, d.y()+rh);
				p.lineTo(-rw, +rh);
				p.lineTo(-rw, -rh);
				p.lineTo(+rw, -rh);
				p.lineTo(d.x()+rw, d.y()-rh);
				p.lineTo(d.x()+rw, d.y()+rh);
				p.closeSubpath();
			}else if(d.x()<0 && d.y()>0){// 2. Quadrant
				p.moveTo(d.x()-rw, d.y()-rh);
				p.lineTo(-rw, -rh);
				p.lineTo(+rw, -rh);
				p.lineTo(+rw, +rh);
				p.lineTo(d.x()+rw, d.y()+rh);
				p.lineTo(d.x()-rw, d.y()+rh);
				p.closeSubpath();
			}else if(d.x()<0 && d.y()<0){// 3. Quadrant
				p.moveTo(d.x()+rw, d.y()-rh);
				p.lineTo(+rw, -rh);
				p.lineTo(+rw, +rh);
				p.lineTo(-rw, +rh);
				p.lineTo(d.x()-rw, d.y()+rh);
				p.lineTo(d.x()-rw, d.y()-rh);
				p.closeSubpath();
			}else{// 4. Quadrant
				p.moveTo(d.x()+rw, d.y()+rh);
				p.lineTo(+rw, +rh);
				p.lineTo(-rw, +rh);
				p.lineTo(-rw, -rh);
				p.lineTo(d.x()-rw, d.y()-rh);
				p.lineTo(d.x()+rw, d.y()-rh);
				p.closeSubpath();
			}
//			// add center line:
//			p.moveTo(0,0);
//			p.lineTo(d);
		}break;
	case Oval:
		// an oval cannot be drawn (isn't specified in the Gerber standard)!
		break;
	}
	return p;
}

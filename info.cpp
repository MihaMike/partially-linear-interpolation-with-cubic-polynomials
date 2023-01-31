#include "info.h"

#include <QGridLayout>
#include <QLabel>

#include <string.h>

Info::Info (const Storage & storage, QWidget * parent)
  : QGroupBox (parent),
    m_storage (storage)
{
  QGridLayout * grid = new QGridLayout (this);

    setTitle ("Info");
    setLayout (grid);

    m_y_min = new QLabel (this);
    m_y_max = new QLabel (this);
    m_residual = new QLabel (this);
    m_zoom = new QLabel (this);

    grid -> addWidget (new QLabel ("y_min and y_max:", this), 0, 0);
    grid -> addWidget (m_y_min, 0, 1, Qt::AlignRight);
    grid -> addWidget (m_y_max, 0, 2, Qt::AlignRight);

    grid -> addWidget (new QLabel ("Residual:", this), 2, 0);
    grid -> addWidget (m_residual, 2, 1, 1, 2, Qt::AlignRight);

    grid -> addWidget (new QLabel ("Zoom factor:", this), 3, 0);
    grid -> addWidget (m_zoom, 3, 1, 1, 2, Qt::AlignRight);
}

void Info::handleUpdate () {
    char buf[32];
    sprintf (buf, "%+.2e", m_storage.getYMin ());
    m_y_min -> setText (buf);
    sprintf (buf, "%+.2e", m_storage.getYMax ());
    m_y_max -> setText (buf);
    sprintf (buf, "%+e", m_storage.getResidual ());
    m_residual -> setText (buf);
    sprintf (buf, "%2d", m_storage.getZoom ());
    m_zoom -> setText (buf);

    /* Console print. */
    printf (">>>>>>>>>>>>>>>>>>>> begin >>>>>>>>>>>>>>>>>>>>\n");
    printf ("Method: %s\n", m_storage.getMethod () .name () .toStdString().c_str());
    printf ("Func: %s\n", m_storage.getFunc () .m_name.toStdString().c_str());
    printf ("Draw:");
    if (m_storage.getNeedDrawFunc ()) {
        printf (" func");
    }
    if (m_storage.getNeedDrawApprox ()) {
        printf ("%s approximation", m_storage.getNeedDrawFunc () ? "," : "");
    }
    if (m_storage.getNeedDrawResidual ()) {
        printf ("%s residual", (m_storage.getNeedDrawFunc () || m_storage.getNeedDrawApprox ()) ? "," : "");
    }
    printf ("\n");
    printf ("Zoom: %2d\n", m_storage.getZoom ());
    printf ("Disturbance: %e\n", m_storage.getDisturbance ());
    printf ("Sector: [%+.2e; %+.2e]\n", m_storage.getA (), m_storage.getB ());
    printf ("n: %10d\n", m_storage.getN ());
    printf ("Y_min and Y_max: %+e, %+e\n", m_storage.getYMin (), m_storage.getYMax ());
    printf ("Residual: %e\n", m_storage.getResidual ());
    printf ("<<<<<<<<<<<<<<<<<<<<< end <<<<<<<<<<<<<<<<<<<<<\n\n");

#ifdef QT_DEBUG
    fprintf (stderr, "Info printed\n");
#endif

}

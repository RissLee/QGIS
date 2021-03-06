# -*- coding: utf-8 -*-

"""
***************************************************************************
    i_gensigset.py
    --------------
    Date                 : March 2016
    Copyright            : (C) 2016 by Médéric Ribreux
    Email                : medspx at medspx dot fr
***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************
"""

__author__ = 'Médéric Ribreux'
__date__ = 'March 2016'
__copyright__ = '(C) 2016, Médéric Ribreux'

# This will get replaced with a git SHA1 when you do a git archive

__revision__ = '$Format:%H$'

import os
from .i import regroupRasters, exportSigFile


def processCommand(alg, parameters, context):
    # We need to extract the basename of the signature file
    signatureFile = alg.parameterAsString(parameters, 'signaturefile', context)
    shortSigFile = os.path.basename(signatureFile)
    parameters['signaturefile'] = shortSigFile

    # Regroup rasters
    group, subgroup = regroupRasters(alg, parameters, context, 'input', 'group', 'subgroup')
    alg.processCommand(parameters, context)

    # Re-add signature files
    parameters['signaturefile'] = signatureFile

    # Export signature file
    exportSigFile(alg, group, subgroup, signatureFile, 'sigset')

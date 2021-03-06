/* 
 * XRG (X Resource Graph):  A system resource grapher for Mac OS X.
 * Copyright (C) 2002-2012 Gaucho Software, LLC.
 * You can view the complete license in the LICENSE file in the root
 * of the source tree.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

//
//  XRGTemperatureMiner.h
//

#import <Foundation/Foundation.h>
#import "XRGDataSet.h"

#define GSDataSetKey			@"DataSet"
#define GSCurrentValueKey		@"CurrentValue"
#define GSUnitsKey				@"Units"
#define GSLabelKey				@"Label"
#define GSEnable				@"Enable"

@class SMCSensors;

@interface XRGTemperatureMiner : NSObject {
    host_name_port_t			host;
    host_basic_info_data_t		hostInfo;
    int                         numCPUs;

    int                         temperatureCounter;			// count and only grab the temperature every 5 seconds.
	
	bool						displayFans;
	NSMutableDictionary			*fanLocations;

@private
    
    int                         numSamples;					// for the XRGDataSets, number of samples to record.
	NSMutableArray				*locationKeysInOrder;		// locations in certain order, returned by locationKeysInOrder, generated by regenerateLocationKeyOrder.
	
	NSMutableDictionary			*sensorData;
    SMCSensors					*smcSensors;
}

- (void)setDataSize:(int)newNumSamples;
- (int)numberOfCPUs;

- (void)setCurrentTemperatures;								// Tries 3 different methods of gathering temperature statistics.
- (void)trySMCTemperature;
- (void)setDisplayFans:(bool)yesNo;

- (NSArray *)locationKeys;									// returns a listing of the location keys (as NSStrings), unordered
- (NSArray *)locationKeysInOrder;							// same as locationKeys, but in a certain order.
- (NSString *)unitsForLocation:(NSString *)location;
- (void)regenerateLocationKeyOrder;
- (float)currentValueForKey:(NSString *)locationKey;
- (void)setCurrentValue:(float)value andUnits:(NSString *)units forLocation:(NSString *)location;
- (XRGDataSet *)dataSetForKey:(NSString *)locationKey;		// If recording a time span of values, returns an XRGDataSet class, 
															// which I can give you the code for early if you want (it hasn't been
															// released yet).
- (NSString *)labelForKey:(NSString *)locationKey;			// return a string label for this location.

@end

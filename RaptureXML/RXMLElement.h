// ================================================================================================
//  RXMLElement.h
//  Fast processing of XML files
//
// ================================================================================================
//  Created by John Blanco on 9/23/11.
//  Version 1.4
//  
//  Copyright (c) 2011 John Blanco
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
// ================================================================================================
//

#import <Foundation/Foundation.h>
#import <libxml2/libxml/xmlreader.h>
#import <libxml2/libxml/xmlwriter.h>
#import <libxml2/libxml/xmlmemory.h>
#import <libxml/xpath.h>
#import <libxml/xpathInternals.h>

@interface RXMLElement : NSObject {
    xmlDocPtr doc_;
    xmlNodePtr node_;
	NSDictionary *attributes_;
}

- (id)initFromXMLString:(NSString *)xmlString encoding:(NSStringEncoding)encoding;
- (id)initFromXMLFile:(NSString *)filename;
- (id)initFromXMLFile:(NSString *)filename fileExtension:(NSString*)extension;
- (id)initFromURL:(NSURL *)url;
- (id)initFromXMLData:(NSData *)data;
- (id)initFromXMLNode:(xmlNodePtr)node;

+ (id)elementFromXMLString:(NSString *)xmlString encoding:(NSStringEncoding)encoding;
+ (id)elementFromXMLFile:(NSString *)filename;
+ (id)elementFromXMLFilename:(NSString *)filename fileExtension:(NSString *)extension;
+ (id)elementFromURL:(NSURL *)url;
+ (id)elementFromXMLData:(NSData *)data;
+ (id)elementFromXMLNode:(xmlNodePtr)node;

+ (id)elementWithTag:(NSString *)tag;

- (NSDictionary *)attributes;

- (NSString *)attribute:(NSString *)attributeName;
- (NSString *)attribute:(NSString *)attributeName inNamespace:(NSString *)ns;

- (NSInteger)attributeAsInt:(NSString *)attributeName;
- (NSInteger)attributeAsInt:(NSString *)attributeName inNamespace:(NSString *)ns;

- (double)attributeAsDouble:(NSString *)attributeName;
- (double)attributeAsDouble:(NSString *)attributeName inNamespace:(NSString *)ns;

- (RXMLElement *)child:(NSString *)tag;
- (RXMLElement *)child:(NSString *)tag inNamespace:(NSString *)ns;

- (NSArray *)children:(NSString *)tag;
- (NSArray *)children:(NSString *)tag inNamespace:(NSString *)ns;
- (NSArray *)childrenWithRootXPath:(NSString *)xpath;

- (void)iterate:(NSString *)query usingBlock:(void (^)(RXMLElement *))blk;
- (void)iterateWithRootXPath:(NSString *)xpath usingBlock:(void (^)(RXMLElement *))blk;
- (void)iterateElements:(NSArray *)elements usingBlock:(void (^)(RXMLElement *))blk;

@property (nonatomic, readonly) NSString *tag;
@property (nonatomic) NSString *text;
@property (nonatomic) NSInteger textAsInt;
@property (nonatomic) double textAsDouble;
@property (nonatomic, readonly) BOOL isValid;

- (RXMLElement *)createElement:(NSString *)tag;
- (RXMLElement *)setElement:(NSString *)tag text:(NSString *)text;

- (RXMLElement *)appendChild:(RXMLElement *)element;
- (RXMLElement *)insertChild:(RXMLElement *)element before:(RXMLElement *)referenceElement;
- (RXMLElement *)insertChild:(RXMLElement *)element after:(RXMLElement *)referenceElement;
- (BOOL)deleteChild:(NSString *)tag;

- (BOOL)setAttribute:(NSString *)attributeName value:(NSString *)value;
- (BOOL)deleteAttribute:(NSString *)attributeName;

typedef enum {
    RXMLWritingOptionNone = 0,
    RXMLWritingOptionIndent = 1 << 0,
} RXMLWritingOptions;

typedef void (^RXMLWriteCompletionHandler)(BOOL success);

- (NSString *)string;
- (NSString *)stringWithOptions:(RXMLWritingOptions)mask;

- (NSData *)data;
- (NSData *)dataWithOptions:(RXMLWritingOptions)mask;

- (void)writeToPath:(NSString *)path options:(RXMLWritingOptions)mask completion:(RXMLWriteCompletionHandler)handler;
- (void)writeToURL:(NSURL*)url options:(RXMLWritingOptions)mask completion:(RXMLWriteCompletionHandler)handler;

@end

typedef void (^RXMLBlock)(RXMLElement *element);

